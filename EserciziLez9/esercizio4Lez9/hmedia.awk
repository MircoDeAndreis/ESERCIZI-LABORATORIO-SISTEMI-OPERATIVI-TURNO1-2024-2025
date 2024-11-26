#!/bin/bash
awk BEGIN {FS=","} 
{
    if (NR>1) hmedia+=$5
    if (NR>1) lines++
} 
END {
    hmedia=hmedia/lines 
    print hmedia
} 

