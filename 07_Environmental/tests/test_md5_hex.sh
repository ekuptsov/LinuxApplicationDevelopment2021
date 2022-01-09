#!/bin/bash

str="Hello,Uneex!"
md5_out=$(echo -n "${str}" | md5sum | cut -d' ' -f 1)
rhasher_out=$(echo -n "MD5 \"${str}\"" | ../builddir/rhasher | cut -d' ' -f 2)
test "${md5_out}" == "${rhasher_out}"
# echo "${md5_out}"
# echo "${rhasher_out}"
