#!/bin/sh
make
rm pipe
mkfifo pipe
echo "Attempting read on a pipe in non-blocking mode"
./readfile pipe nonblock
