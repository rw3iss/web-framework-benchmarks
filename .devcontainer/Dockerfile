#ARG VARIANT=buster
FROM rust:latest
FROM node:latest
FROM golang:latest

RUN apt-get update -y && apt-get upgrade -y && apt-get dist-upgrade -y

# Apache Benchmark:
RUN apt-get -y install apache2-utils


# Rust:
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"
#############################################################


# Go:
RUN go get github.com/go-sql-driver/mysql
#############################################################


# Node:
## NODE + ESBUILD REQUIREMENTS ###
RUN curl -sL https://deb.nodesource.com/setup_15.x | bash -
RUN apt-get -y install nodejs
#RUN sudo npm install nodemon esbuild -g
#############################################################


# JustJS:
ARG VARIANT=buster
#FROM debianbuster
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends sudo g++ make libffi-dev bzip2 gdb \
    && apt-get clean -y && rm -rf /var/lib/apt/lists/* /tmp/library-scripts
## used by modules for just.h - needed for "runtime-builder" build
ENV JUST_HOME=/workspaces/just
## add just
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/just
## target directory for "just build"
ENV JUST_TARGET=/workspaces/just
#############################################################


# Drogon:
RUN apt-get update -yqq \
    && apt-get install -yqq --no-install-recommends software-properties-common \
    sudo curl wget cmake pkg-config locales git gcc-8 g++-8 \
    openssl libssl-dev libjsoncpp-dev uuid-dev zlib1g-dev libc-ares-dev\
    postgresql-server-dev-all libmariadbclient-dev libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8

ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    CC=gcc-8 \
    CXX=g++-8 \
    AR=gcc-ar-8 \
    RANLIB=gcc-ranlib-8 \
    IROOT=/workspace/benchmarks/src/drogon

ENV DROGON_ROOT="$IROOT/drogon_src"

RUN mkdir /install
RUN mkdir /install/drogon

ADD https://api.github.com/repos/an-tao/drogon/git/refs/heads/master $IROOT/version.json
RUN git clone https://github.com/an-tao/drogon $DROGON_ROOT

WORKDIR $DROGON_ROOT

RUN ./build.sh
#############################################################


EXPOSE 8080 8081 3000 9222