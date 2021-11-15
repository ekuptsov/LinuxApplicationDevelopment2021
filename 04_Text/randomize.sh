#!/bin/sh

# /bin/echo -e "п" | iconv -f UTF8 -t UCS-2 | for i in $(hexdump -v -e '2/1 "\\x%02x"" "'); do /bin/echo -e -n $i | iconv -f UCS-2 -t UTF8; done
# transparent foreground on white background
# echo -e "\e[38;5;0;48;5;255m{text}\e[0m"

tput reset
delay=$1
TEXT=""
pos_i=0
pos_j=0

for rune in $(iconv -f UTF8 -t UCS-2 | hexdump -v -e '2/1 "\\x%02x"" "')
do
    TEXT="$TEXT$pos_i\t$pos_j\t$rune\n"
    pos_j=$(($pos_j + 1))
    if [ "$rune" = "\x0a\x00" ]
    then
        pos_i=$(($pos_i + 1))
        pos_j=0
    fi
done
last_i=$pos_i
last_j=$pos_j

printf "$TEXT" | shuf | while read -r piece
do
    sleep $delay

    pos_i=$(echo "$piece" | cut -f 1)
    pos_j=$(echo "$piece" | cut -f 2)
    rune=$(echo "$piece"  | cut -f 3)

    tput cup $pos_i $pos_j
    /bin/echo -en "$rune" | iconv -f UCS-2 -t UTF8
done
tput cup $last_i $last_j