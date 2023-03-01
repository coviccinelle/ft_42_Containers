!#bin/bash

#flags=""

#if [[ "$1" == "--nice_mode" ]] || [[ "$1" == "-n" ]]; then
#   nice=1
#fi

#if [[ "$1" == "-d" ]]
#	flags+="--gtest_also_run_disabled_tests"
#fi
make retet_int && ./tests --gtest_also_run_disabled_tests
