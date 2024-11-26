#!/bin/bash

for i in `ipcs -q | grep 0x | awk '{print $2}'`;
    do
        ipcrm -q $i;
    done