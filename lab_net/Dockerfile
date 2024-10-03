FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get upgrade -y && apt-get install -y tini tmux htop vim \
	man manpages procps less net-tools wget curl dnsutils iputils-ping python3-netifaces \
	iptables iproute2 tcpdump dnsmasq nginx python3-certbot-nginx openssl easy-rsa openssh-server

# for sshd
RUN mkdir -p /run/sshd
RUN mkdir -p -m 0700 /root/.ssh
COPY ./conf/ssh/id_* /root/.ssh/
COPY ./conf/ssh/id_ed25519.pub /root/.ssh/authorized_keys

ENTRYPOINT [ "/usr/bin/tini", "-g", "--" ]
CMD [ "/usr/bin/sleep", "infinity" ]
