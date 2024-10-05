#!/bin/sh
ssh -p 30022 -i ../conf/ssh/id_ed25519 root@localhost -L 20080:gw:80 -L 20443:gw:443
