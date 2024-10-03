#!/bin/sh

echo '-  eth0:' `/scripts/if.py eth0`
echo -n '- route: '
ip route show default

echo 'Press any key to continue or Ctrl-C to break ...'
read ___

if [ ! -z "$1" ]; then
	GWADDR=$1
	ip route del default
	ip route add default via $GWADDR
fi

ip link add vxlan1 type vxlan id 5001 group 239.1.1.1 dev eth10 dstport 4789	# LAN
ip link add vxlan2 type vxlan id 5002 group 239.1.1.2 dev eth20 dstport 4789	# DMZ

ip addr add 10.140.112.254/24 dev vxlan1	# LAN
ip addr add 10.140.113.254/24 dev vxlan2	# DMZ

ip link set vxlan1 up
ip link set vxlan2 up

