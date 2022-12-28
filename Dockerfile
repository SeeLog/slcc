# Usage:
#   docker build -t slcc .
FROM ubuntu:22.04

RUN apt update && apt upgrade -y
RUN apt install -y locales tzdata

# Japanese environment
RUN locale-gen ja_JP.UTF-8
ENV LANG ja_JP.UTF-8
ENV LANGUAGE ja_JP:ja
ENV LC_ALL ja_JP.UTF-8

RUN apt install -y zsh gcc make git binutils libc6-dev gdb sudo

ENV USER=ubuntu GROUP=ubuntu
RUN groupadd -g 1000 -r $GROUP && \
  useradd --create-home --no-log-init -r -s /bin/zsh -u 1000 -g $GROUP $USER

USER ubuntu
WORKDIR /home/ubuntu
