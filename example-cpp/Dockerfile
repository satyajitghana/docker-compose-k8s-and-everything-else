FROM gcc:9.4.0 as builder

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
RUN echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ bionic main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null
RUN apt-get update -y && apt-get install -y --no-install-recommends \
	cmake

WORKDIR /opt

ADD . .

RUN cmake . && make && ctest --output-on-failure

FROM alpine:3.14 as runtime

RUN apk upgrade --no-cache && \
	apk add --no-cache libc6-compat libgcc libstdc++

WORKDIR /opt/hello-world

COPY --from=builder /opt/helloworld ./

CMD ["./helloworld"]