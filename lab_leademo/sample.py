#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import hashlib

def simple_parser(qstr):
    parsed = {}
    for param in qstr.split(b'&'):
        (p, v) = param.split(b'=', 1)
        parsed[p] = v
    return parsed;

def hmac(qstr):
    secret = b'secret|'
    return hashlib.md5(secret + qstr[:qstr.find(b'&hmac=')]).hexdigest()

msg = b'action=deposit&money=100'
old_mac = b'&hmac=ceeff68a6bff37adc8dfccf6d5fb0a25'
query = simple_parser(msg + old_mac)
print(query)
print(hmac(msg + old_mac))
print('Passed:', hmac(msg + old_mac) == query[b'hmac'].decode('ascii'))

# LEA generated padding & new_mac for the appended message
append = b'&money=100000000'
padding = b'\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf8\x00\x00\x00\x00\x00\x00\x00'
new_mac = b'&hmac=efc7253c26495b391e53f325d293e821'
query = simple_parser(msg + padding + append + new_mac)
print(query)
print(hmac(msg + padding + append + new_mac))
print('Passed:', hmac(msg + padding + append + new_mac) == query[b'hmac'].decode())


# vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4 number cindent fileencoding=utf-8 :
