#!/bin/bash

str="Hello,Uneex!"
sha1_out=$(echo -n "${str}" | sha1sum | cut -d' ' -f 1)
rhasher_out=$(echo -n "sha1 \"${str}\"" | ../builddir/rhasher | cut -d' ' -f 2 | base64 -d | od -t x1 -An | tr -d [:space:])
test "${sha1_out}" == "${rhasher_out}"
echo "${sha1_out}"
echo "${rhasher_out}"
