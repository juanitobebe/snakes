FROM ubuntu:latest

ENV TZ=America/Los_Angeles
ENV GBDK2020_VERSION 3.1
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y git build-essential sdcc
ENV SDCCDIR=/usr

WORKDIR /tmp
RUN git clone --branch v$GBDK2020_VERSION https://github.com/Zal0/gbdk-2020.git
RUN cd /tmp/gbdk-2020 && make
RUN cp -r /tmp/gbdk-2020/build/gbdk /opt
ENV PATH="/opt/gbdk/bin:${PATH}"
WORKDIR /opt
RUN mkdir snake