FROM frolvlad/alpine-glibc:latest

# GBDK-2020 version based on GitHub releases
ENV GBDK2020_VERSION 4.0.2

# install wget, make and libstdc++
RUN apk add --no-cache wget make libstdc++

RUN wget https://github.com/Zal0/gbdk-2020/releases/download/${GBDK2020_VERSION}/gbdk-linux64.tar.gz
RUN tar -xf gbdk-linux64.tar.gz
RUN rm gbdk-linux64.tar.gz
RUN cp -r gbdk/ /opt
ENV PATH="/opt/gbdk/bin:${PATH}"
WORKDIR /opt/snakes

