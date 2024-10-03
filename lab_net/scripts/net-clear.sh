#!/bin/sh

ip link set vxlan1 down
ip link set vxlan2 down

ip link del vxlan1
ip link del vxlan2

