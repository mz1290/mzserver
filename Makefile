SHELL :=	/bin/sh
PWD :=		$(shell pwd)

container: image
	docker container run \
	-it --rm \
	-v $(PWD):/home \
	mzserverdev sh

image: Dockerfile
	docker image build \
	-t mzserverdev .

clean:
	rm -rf client server