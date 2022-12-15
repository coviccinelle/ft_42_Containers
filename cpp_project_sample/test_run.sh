!#bin/bash

nice=0

if [[ "$1" == "--nice_mode" ]] || [[ "$1" == "-n" ]]; then
    nice=1
fi

make retet_int "NICE=$nice" && ./tests
