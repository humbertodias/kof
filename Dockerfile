FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y && \
    apt install -y cmake build-essential curl git pkg-config zip \
    libxmu-dev libxi-dev libgl-dev libglu1-mesa-dev \
    autoconf automake autoconf-archive \
    libltdl-dev python3 python3-jinja2 ninja-build