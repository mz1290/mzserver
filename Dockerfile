FROM alpine

# alpine tini init
RUN apk add --no-cache tini
RUN apk update
RUN apk add build-base git gdb vim wget curl make automake autoconf cmake

WORKDIR /home

CMD ["/sbin/tini", "--"]
