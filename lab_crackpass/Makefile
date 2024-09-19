
IMAGE	= chuang/lab-crackpass

all:
	@echo 'make { docker-build | docker-run }'

docker-build:
	docker build -t $(IMAGE) .

docker-run:
	docker run -it --rm -v "$(shell pwd)/samples:/workdir" -w /workdir $(IMAGE)
