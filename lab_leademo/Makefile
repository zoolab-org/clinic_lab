
IMAGE	= chuang/lab-leademo

CFLAGS	+= -g -Wall $(shell pkg-config --cflags mbedtls mbedcrypto 2> /dev/null)
LDFLAGS	= $(shell pkg-config --libs mbedtls mbedcrypto 2> /dev/null || echo '-lmbedtls -lmbedcrypto')

PROGS	= md5demo

all: $(PROGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

md5demo: md5demo.o
	$(CC) -o $@ $^ $(LDFLAGS)

run: $(PROGS)
	./md5demo

docker-build:
	docker build -t $(IMAGE) .

docker-run:
	docker run -it --rm -v "$(shell pwd):/workdir" -w /workdir --user $(shell id -u):$(shell id -g) $(IMAGE) bash

docker-run-root:
	docker run -it --rm -v "$(shell pwd):/workdir" -w /workdir $(IMAGE) bash

clean:
	rm -f *.o $(PROGS)

