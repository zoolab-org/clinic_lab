#!/bin/sh

if [ -z "$1" ]; then
	echo $0 '<user-ip-address, e.g., 10.140.112.x>'
	exit 1
fi

USERIP=$1

ip route del default
ip link add vxlan1 type vxlan id 5001 group 239.1.1.1 dev eth10 dstport 4789
ip addr add $USERIP/24 dev vxlan1
ip link set vxlan1 up
ip route add default via 10.140.112.254

