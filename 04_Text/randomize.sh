#!/bin/sh
tput reset
delay=$1
RES=""
i=0
j=0
for p in $(hexdump -v -e '1/1 "%x "')
do
    RES="$RES$i\t$j\t\x$p\n"
    j=$(($j + 1))
    if [ "$p" = "a" ]
    then
        i=$(($i + 1))
        j=0
    fi
done

printf "$RES" | shuf | while read -r piece
do
    sleep $delay
    ii=$(echo "$piece" | cut -f 1)
    jj=$(echo $piece | cut -d' ' -f 2)
    hx=$(echo "$piece" | cut -f 3)
    tput cup $ii $jj
    /bin/echo -e $hx
done
tput cup $i $j