#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import socket

if len(sys.argv) < 2:
    print('127.0.0.1')
    sys.exit(0)

try:
    print(socket.gethostbyname(sys.argv[1]))
except:
    print('0.0.0.0')


# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
