#!/bin/bash
rm /tmp/listFinal.txt
ps c --user $(whoami) >> /tmp/list1.txt
word=$(wc -w /tmp/list1.txt)
word=${word:0:4}
div=$(( word * 100 / 2 % 100 ))
if [ $div != 0 ]; then
            echo "999" >> /tmp/list1.txt
        fi
tsort /tmp/list1.txt > /tmp/list2.txt
rm /tmp/list1.txt

index=0
while read line; do
    for((a=0; a < ${#line}; a++))
        do
            kk=$line
		if [ "$kk" != "PID" ] && [ "$kk" != "TTY" ] && [ "$kk" != "Rl" ] && [ "$kk" != "pts/1" ]  && [ "$kk" != "pts/3" ] && [ "$kk" != "CMD" ] && [ "$kk" != "TIME" ] && [ "$kk" != "<defunct>" ] && [ "$kk" != "COMMAND" ] && [ "$kk" != "S<l" ] && [ "$kk" != "STAT" ] && [ "$kk" != "Z" ] && [ "$kk" != "R" ] && [ "$kk" != "Ssl" ] && [ "$kk" != "Ss+" ] && [ "$kk" != "Sl" ] && [ "$kk" != "S" ] && [ "$kk" != "Ss" ] && [ "$kk" != "SLl" ] && [ "$kk" != "ps" ] && [ "$kk" != "getAllUsersProg" ] && [ "$kk" != "S+" ] && [ "$kk" != "R+" ] && [ "$kk" != "pts/2" ];
		    then 
			    k=${kk:$a:1}
			    if [ "$k" != 0 ] && [ "$k" != 1 ] && [ "$k" != 2 ] && [ "$k" != 3 ] && [ "$k" != 4 ] && [ "$k" != 5 ] && [ "$k" != 6 ] && [ "$k" != 7 ] && [ "$k" != 8 ] && [ "$k" != 9 ] && [ "$k" != '?' ] && [ "$k" != '!' ];
				then
				    array[$index]="$kk"
				    index=$(($index+1))
				    break
				else
				    break
			    fi;
		    else 
			echo "Bad procces"
		    fi;
        done
done < /tmp/list2.txt

for i in "${array[@]}"; do echo $i >> /tmp/list1.txt; done
rm /tmp/list2.txt
sort /tmp/list1.txt >> /tmp/listFinal.txt
rm /tmp/list1.txt
exit

