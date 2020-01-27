#!/bin/sh
make
rm pipe
mkfifo pipe
echo "Attempting read on a pipe, will block"
echo "Run \"echo 'hi' > pipe\" from another window to unblock"
./readfile pipe
