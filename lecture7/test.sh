#!/bin/bash
# Test script for threaded withdraw applicaiton
# Tries to complete 1000 iterations on withdraw_threaded with
# arguments passed, breaks out early if an error occurs.

exit_fail=0
iteration=0
tmpfile=`mktemp`
while [ $exit_fail -eq 0 ]
do
    ./withdraw_threaded $@
    exit_fail=$?
    ((iteration=$iteration+1))
    if [ $iteration -gt 1000 ]; then
        break
    fi
done
if [ $exit_fail -ne 0 ]; then
    cat $tmpfile
    echo "Last execution failed at iteration $iteration"
else
    echo "Completed $iteration iterations without failure using arguments $@"
fi
exit $exit_fail
