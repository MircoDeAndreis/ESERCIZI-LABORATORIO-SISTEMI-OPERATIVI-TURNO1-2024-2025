#!/bin/bash
if [ $1 ]
then 
    if [ -d $1 ]
    then
        ls -l $1
    else
        cat $1
    fi 
else
    echo "errore "
fi
