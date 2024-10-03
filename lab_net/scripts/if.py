#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import netifaces as ni

if len(sys.argv) < 2:
    print('0.0.0.0')
    sys.exit(0)

try:
    print(ni.ifaddresses(sys.argv[1])[ni.AF_INET][0]['addr'])
except:
    print('127.0.0.1')


# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
