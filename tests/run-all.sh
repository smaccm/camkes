#!/bin/bash
#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

export QEMU_KZM=${QEMU_KZM:-qemu-system-arm}
export QEMU_IA32=${QEMU_IA32:-qemu-system-i386}

RESULT=0

for t in $(ls tests); do
    if [ "$t" != "run-all.sh" ]; then
        if [[ -x "tests/$t" ]]; then
            echo -n " Running $t ... "
            ./tests/$t &>/dev/null
            if [ $? -ne 0 ]; then
                echo -e "\033[31mFailed\033[0m"
                RESULT=1
            else
                echo -e "\033[32mPassed\033[0m"
            fi
        fi
    fi
done

exit ${RESULT}
