#!/bin/sh
make
rm -f pipe
mkfifo pipe
# Open a command for reading the pipe and put in the background.
# This prevents the next command from blocking
# See https://unix.stackexchange.com/questions/366219/prevent-automatic-eofs-to-a-named-pipe-and-send-an-eof-when-i-want-it
echo < pipe &
# Open a command to write to the pipe, but don't write anything.  This means we will get EAGAIN from the READ instead of
# EOF
exec 3>pipe
echo "Attempting read on a pipe in non-blocking mode"
./readfile pipe nonblock
