FROM kalilinux/kali-rolling:latest

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get upgrade -y && apt-get install -y sudo tmux htop vim curl less john wordlists \
		zip openssh-client
