#!/bin/bash
ps -elf | grep Parking > ps.txt;
awk '{print $15} {print $4}' ps.txt > tmp1.txt
key1=`awk '{print $1}' tmp1.txt`
echo $key1 > id.txt
counter=0
for i in $key1
do counter=$((counter+1))
if [ "$i" = "./Parking" ]
then
tampon=$((counter+1))
echo $tampon
id=`awk '{print $tampon}' id.txt`
echo $id
fi
done
#rm f.txt
#rm memoire.txt


