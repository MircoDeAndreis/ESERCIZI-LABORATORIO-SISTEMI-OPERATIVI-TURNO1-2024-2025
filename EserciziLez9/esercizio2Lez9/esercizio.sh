#!/bin/bash
#for i in {1..10}
#do 
#    cp 1.txt "$i.txt"
#    chmod 777 $i.txt
#done
rm all_content.txt
touch all_content.txt
chmod 777 all_content.txt
for i in {1..10}
do
    less $i.txt >> all_content.txt 
done
less all_content.txt 