#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <mbedtls/md5.h>

#define	MD5_BLOCK_SIZE	64
#define	MD5_DIGEST_SIZE	16

#if MBEDTLS_VERSION_MAJOR == 3
#include <mbedtls/compat-2.x.h>
#endif

/* ths structure MUST be exact the same as mbedtls_md5_context */
typedef struct {
	uint32_t total[2];        /*!< The number of Bytes processed.  */
	uint32_t state[4];        /*!< The intermediate digest state.  */
	unsigned char buffer[64]; /*!< The data block being processed. */
}	HASH_CONTEXT;

void hex_to_bytes(const char *hex, uint8_t *bytes, size_t byte_len) {
	for (size_t i = 0; i < byte_len; i++) {
		sscanf(hex + 2 * i, "%2hhx", &bytes[i]);
	}
}

char * bytes_to_hex(const uint8_t *bytes, size_t byte_len, char *hex, size_t hex_len) {
	size_t i;
	if(hex == NULL || hex_len < 0) return NULL;
	hex[0] = 0;
	for(i = 0; i < byte_len && (i+1)*2 < hex_len; i++) {
		snprintf(hex + 2 * i, 3, "%2.2x", bytes[i]);
	}
	return hex;
}

int md5_padding(uint64_t message_len, uint8_t *padding, size_t padding_length) {
	uint64_t bit_length = message_len * 8;
	size_t pad_len = MD5_BLOCK_SIZE - (message_len % MD5_BLOCK_SIZE);

	if (pad_len < 9) {
		pad_len += MD5_BLOCK_SIZE;
	}

	if(padding_length < pad_len) return -1;

	padding[0] = 0x80;
	memset(padding + 1, 0, pad_len - 9);

	for (int i = 0; i < 8; i++) {	// LITTLE-endian
		padding[pad_len - 8 + i] = (uint8_t)(bit_length >> (8 * i));
	}

	return pad_len;
}

int length_extension_attack(const uint8_t *old_hash, const uint8_t *append_data, size_t append_len, uint64_t message_len, size_t key_len, uint8_t *padding, size_t padding_len, uint8_t *new_hash) {
	mbedtls_md5_context ctx;
	HASH_CONTEXT *pctx = (HASH_CONTEXT*) &ctx;
	uint64_t total_len;

	// Create the padding for the original message + key
	padding_len = md5_padding(key_len + message_len, padding, padding_len);
	assert(padding_len > 8);

	// Initialize the context with the original hash state
	mbedtls_md5_init(&ctx);

	// Set the state with the original hash
	memcpy(pctx->state, old_hash, MD5_DIGEST_SIZE);
	total_len = key_len + message_len + padding_len;
	pctx->total[0] = total_len & 0xffffffff;
	pctx->total[1] = total_len >> 32;

	// Update the context with the new data (after padding)
	assert(mbedtls_md5_update_ret(&ctx, append_data, append_len) == 0);

	// Finalize the hash computation
	assert(mbedtls_md5_finish_ret(&ctx, new_hash) == 0);

	// Clean up
	mbedtls_md5_free(&ctx);

	return padding_len;
}

static const char secret[] = "unknownSecretKey";
static const int  secret_len = sizeof(secret) - 1;
static const char message[] = "message";
static const int  msg_len = sizeof(message) - 1;
static const char old_hash[] = "f98a9b28a0a6d3a680542b9d64502949";		// echo -n 'unknownSecretKeymessage' | md5sum

int main() {
	char charbuf[256] = "";
	const char append[] = ";admin=true";
	uint8_t output[MD5_DIGEST_SIZE];
	mbedtls_md5_context ctx;
	HASH_CONTEXT *pctx = (HASH_CONTEXT*) &ctx;
	uint8_t padding[MD5_BLOCK_SIZE + 8];  // Enough space for padding and message length
	size_t padding_len;

	// Show original hash
	printf("# Known Hash:   %s\n", old_hash);

	// Check mbedtls MD5 function 
	mbedtls_md5_init(&ctx);
	assert(mbedtls_md5_starts_ret(&ctx) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) secret, secret_len) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) message, msg_len) == 0);
	assert(mbedtls_md5_finish_ret(&ctx, output) == 0);
	mbedtls_md5_free(&ctx);
	printf("# mbedTLS Hash: %s\n", bytes_to_hex(output, MD5_DIGEST_SIZE, charbuf, sizeof(charbuf)-1));

	// LEA
	padding_len = length_extension_attack(output, (uint8_t *) append, strlen(append), msg_len, secret_len, padding, sizeof(padding), output);
	printf("# Padding: (%zd) %s\n", padding_len, bytes_to_hex(padding, padding_len, charbuf, sizeof(charbuf)-1));
	printf("# New Hash: %s\n", bytes_to_hex(output, MD5_DIGEST_SIZE, charbuf, sizeof(charbuf)-1));

	// DEBUG result
	mbedtls_md5_init(&ctx);
	assert(mbedtls_md5_starts_ret(&ctx) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) secret, secret_len) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) message, msg_len) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) padding, padding_len) == 0);
	printf("# DEBUG State: (%zd) %s\n", secret_len + msg_len + padding_len,
		bytes_to_hex((uint8_t *) pctx->state, MD5_DIGEST_SIZE, charbuf, sizeof(charbuf)-1));

	// Verify result
	mbedtls_md5_init(&ctx);
	assert(mbedtls_md5_starts_ret(&ctx) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) secret, secret_len) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) message, msg_len) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) padding, padding_len) == 0);
	assert(mbedtls_md5_update_ret(&ctx, (uint8_t *) append, strlen(append)) == 0);
	assert(mbedtls_md5_finish_ret(&ctx, output) == 0);
	mbedtls_md5_free(&ctx);
	printf("# Verified: %s\n", bytes_to_hex(output, MD5_DIGEST_SIZE, charbuf, sizeof(charbuf)-1));

	return 0;
}

