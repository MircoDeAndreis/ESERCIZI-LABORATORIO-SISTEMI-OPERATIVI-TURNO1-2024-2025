#!/bin/bash

for i in `ipcs -s | grep 0x | awk '{print $2}'`;
    do
        ipcrm -s $i;
    done