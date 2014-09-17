#!/bin/bash
ipcs -m > memoire.txt;
awk '{print $1}' memoire.txt > tmp1.txt
awk '{print $1}' IPCS_MemoirePartagee.txt > tmp2.txt
diff tmp1.txt tmp2.txt | awk '{$1=""; print $0}' > f.txt
key1=`awk '{print $1}' f.txt`
for i in $key1
do if [ "$i" != "0x00000000" ]
then
ipcrm -M $i
fi
done
rm f.txt
rm memoire.txt
#----------------------------------#
ipcs -s > sem.txt
awk '{print $1}' sem.txt > tmp1.txt
awk '{print $1}' IPCS_Semaphore.txt > tmp2.txt
diff tmp1.txt tmp2.txt | awk '{$1=""; print $0}' > f.txt
key2=`awk '{print $1}' f.txt`
for i in $key2
do if [ "$i" != "0x00000000" ]
then
ipcrm -S $i
fi
done
rm f.txt
rm sem.txt
#-----------------------------------#
ipcs -q > BAL.txt
awk '{print $1}' BAL.txt > tmp1.txt
awk '{print $1}' IPCS_FiledeMessage.txt > tmp2.txt
diff tmp1.txt tmp2.txt | awk '{$1=""; print $0}' > f.txt
key3=`awk '{print $1}' f.txt`
for i in $key3
do if [ "$i" != "0x00000000" ]
then
ipcrm -Q $i
fi
done
rm f.txt
rm BAL.txt
rm tmp1.txt
rm tmp2.txt

