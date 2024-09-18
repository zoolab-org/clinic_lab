
IMAGE	= chuang/lab-opmode

all:
	@echo 'make { docker-build | docker-run }'

docker-build:
	docker build -t $(IMAGE) .

docker-run:
	docker run -it --rm -v "$(shell pwd):/workdir" -w /workdir --user "$(shell id -u):$(shell id -g)" $(IMAGE)

docker-run-root:
	docker run -it --rm -v "$(shell pwd):/workdir" -w /workdir $(IMAGE)

clean:
	rm -f tux.enc tux.enc.png tux.enc.raw tux.raw

