FROM ubuntu:14.04

MAINTAINER Nathan Barrett Morrison version: 0.1

RUN apt-get update && apt-get install -y make g++

WORKDIR /usr/pencil-degradation
COPY . .

RUN make clean
RUN make

CMD ["./build/pencilDegradation-test"]
