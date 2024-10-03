#!/bin/sh

ip route del default
ip link add vxlan2 type vxlan id 5002 group 239.1.1.2 dev eth20 dstport 4789
ip addr add 10.140.113.100/24 dev vxlan2
ip link set vxlan2 up
ip route add default via 10.140.113.254

