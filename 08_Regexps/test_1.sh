#!/bin/bash

r='(a.*)(b.*)c'
sb='rfh\\gjsgh'
st='aqqbqqckl'

res_sed=$(echo ${st} | sed -E s/$r/${sb}/)
res_esub=$(../builddir/esub $r ${sb} ${st})
echo $res_sed
echo $res_esub
test $res_sed == $res_esub

