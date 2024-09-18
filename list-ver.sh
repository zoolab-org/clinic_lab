#!/bin/sh

find . -name Dockerfile -exec grep -H FROM {} \;
