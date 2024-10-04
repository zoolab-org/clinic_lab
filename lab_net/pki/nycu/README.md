
# Get certificates

`openssl s_client -showcerts -connect www.nycu.edu.tw:443 < /dev/null > /tmp/cert.raw`

# Display content from certificates

You need to extract certificates from the `cert.raw` file. Here are the samples we extracted from the sample file.

```
openssl x509 -in c-nycu.pem -text -noout
openssl x509 -in c-twca.pem -text -noout
```

# Verify the certificate

```
openssl verify c-nycu.pem                          # should be failed
openssl verify c-twca.pem                          # should be passed
openssl verify -untrusted c-twca.pem c-nycu.pem    # should be passed
```

