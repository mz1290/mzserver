SHELL :=	/bin/sh
PWD :=		$(shell pwd)

run: compile-client compile-server docker-compose.yaml
	docker-compose up -d && \
	docker exec -it mzserver_client_1 /bin/ash

run-client: compile-client
	./client

run-server: compile-server
	./server

compile-client: client.c
	gcc -O0 -g client.c -o client

compile-server: server.c
	gcc -O0 -g server.c -o server

container: image
	docker container run \
	-it --rm \
	-v $(PWD):/home \
	mzserverdev sh

image: Dockerfile
	docker image build \
	-t mzserverdev .

stop: docker-compose.yaml
	docker-compose stop

clean:
	rm -rf client server \
	docker-compose down