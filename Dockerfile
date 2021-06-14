FROM alpine

RUN apk update
RUN apk add build-base git gdb vim wget curl make automake autoconf cmake

WORKDIR /home
