#!/bin/sh

cpus=$(grep -c ^processor /proc/cpuinfo)

cd tor-client-src
./configure
make -j $cpus

cp src/or/tor ../tor-client

# http://linux.byexamples.com/archives/163/how-to-create-patch-file-using-patch-and-diff/
