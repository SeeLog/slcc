# Usage:
#   docker build -t slcc .
FROM ubuntu:22.04

RUN apt-get update && apt-get upgrade -y \
  && apt-get install -y locales tzdata \
  && locale-gen ja_JP.UTF-8
ENV LANG ja_JP.UTF-8
ENV LANGUAGE ja_JP:ja
ENV LC_ALL ja_JP.UTF-8

RUN apt-get install -y zsh gcc make git binutils libc6-dev gdb sudo

RUN useradd -m -s /bin/zsh ubuntu

USER ubuntu
WORKDIR /home/ubuntu
