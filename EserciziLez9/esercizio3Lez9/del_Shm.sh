#!/bin/bash

for i in `ipcs -m | grep 0x | awk '{print $2}'`;
    do
        ipcrm -m $i;
    done