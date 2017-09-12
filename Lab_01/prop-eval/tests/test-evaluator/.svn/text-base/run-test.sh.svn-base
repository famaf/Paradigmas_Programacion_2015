#!/bin/bash
FOLDER=$1
TEST=./test-eval
TS=$(date +%s)
LOG=test-$TS.log
echo "Ejecutando tests sobre carpeta:" $FOLDER > $LOG
echo "-----------------------------------" >> $LOG
ok=0
fail=0
for f in $(find $FOLDER -type f -name "*.frm")
do
    g=$(basename $f)
    p=${g%.*}
    for a in $(find $FOLDER -type f -name "$p-*.asg")
    do
	#obtenemos el resultado esperado 
	s=${a##*-}
	e=${s%.*}

	#ejecutamos la prueba
	m="$($TEST $f $a 2>&1)"
	mark=""
	# chequeamos el resultado contra lo esperado
	if [ "$e" = "$m" ];
	then
     	    ok=$((ok+1))
     	    mark=""
	else
     	    fail=$((fail+1))
     	    mark="*"
	fi
	# logueamos el resultado
	echo $mark"ve:"$e" - vo:"$m " - formula:"$g " - asg:"$(basename $a)   >> $LOG

    done
done

 echo "-----------------------------------" >> $LOG
 echo "OK:" $ok " - ERROR:" $fail >> $LOG
 cat $LOG
# 
