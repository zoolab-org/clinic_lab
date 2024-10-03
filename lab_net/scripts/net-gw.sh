#!/bin/sh

if [ -z "$1" ]; then
	echo eth0: `/scripts/if.py eth0`
	echo $0 '<gateway-ip-address>'
	exit 1
fi

GWADDR=$1
ip route del default
ip route add default via $GWADDR

ip link add vxlan1 type vxlan id 5001 group 239.1.1.1 dev eth10 dstport 4789	# LAN
ip link add vxlan2 type vxlan id 5002 group 239.1.1.2 dev eth20 dstport 4789	# DMZ

ip addr add 10.140.112.254/24 dev vxlan1	# LAN
ip addr add 10.140.113.254/24 dev vxlan2	# DMZ

ip link set vxlan1 up
ip link set vxlan2 up

