SHELL :=	/bin/sh
PWD :=		$(shell pwd)

run-client-server: compile-client compile-server docker-compose.yaml
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

container-server: image
	docker container run \
	-it --rm \
	-p 8080:8080 \
	-v $(PWD):/home \
	mzserverdev /bin/ash

container: image
	docker container run \
	-it --rm \
	-v $(PWD):/home \
	mzserverdev /bin/ash

image: Dockerfile
	docker image build \
	-t mzserverdev .

stop: docker-compose.yaml
	docker-compose stop

clean:
	rm -rf client server \
	docker-compose down