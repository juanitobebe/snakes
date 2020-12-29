FROM ubuntu:latest

ENV TZ=America/Los_Angeles
ENV GBDK2020_VERSION v4.0
ENV SDCC_COMMIT 11929
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install -y git curl subversion build-essential flex bison libboost-dev \
    texinfo zip netcat gawk python2.7 libz-dev \
    && apt-get autoclean
ENV SDCCDIR=/usr/local

RUN mkdir /sdcc -p \
    && cd /sdcc \
    && svn checkout svn://svn.code.sf.net/p/sdcc/code/trunk/sdcc@${SDCC_COMMIT} \
    && cd sdcc \
    && ./configure --disable-pic14-port --disable-pic16-port \
    && make && make install \
    && cd / \
    && rm -Rf /sdcc /tmp/*

WORKDIR /tmp
RUN git clone --branch $GBDK2020_VERSION https://github.com/Zal0/gbdk-2020.git
RUN cd /tmp/gbdk-2020 && make
RUN cp -r /tmp/gbdk-2020/build/gbdk /opt
ENV PATH="/opt/gbdk/bin:${PATH}"
WORKDIR /opt
RUN mkdir snake
