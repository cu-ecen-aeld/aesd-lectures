#!/bin/bash
# A script to auto generate test runners for unity tests
cd `dirname $0`
set -e
pushd ..
mkdir -p test/test_runners
# See https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityHelperScriptsGuide.md
ruby Unity/auto/generate_test_runner.rb test/Test_time_functions_shared.c test/test_runners/Test_time_functions_shared_Runner.c
