#!/bin/bash
FOLDER=$1
EXT=$2
TEST=./test-aparser
TS=$(date +%s)
LOG=test-$TS.log
echo "Ejecutando tests sobre carpeta:" $FOLDER > $LOG
echo "Extension de las asignaciones: *."$EXT >>$LOG
echo "-----------------------------------" >> $LOG
ok=0
fail=0
for f in $(find $FOLDER -type f -name "*.$EXT")
do
    #obtenemos el resultado esperado 
    s=${f##*-}
    e=${s%.*}
    #ejecutamos la prueba
    m="$($TEST $f 2>&1)"
    o=$?
    mark=""
    #chequeamos el resultado contra lo esperado
    if [ $e -eq $o ];
    then
	ok=$((ok+1))
	mark=""
    else
	fail=$((fail+1))
	mark="*"
    fi
    #logueamos el resultado
    echo $mark"ve:"$e" - vo:"$o" - output: "$m >> $LOG
done

echo "-----------------------------------" >> $LOG
echo "OK:" $ok " - ERROR:" $fail >> $LOG
cat $LOG
#echo "OK:" $ok " - ERROR:" $fail " - ARCHIVO LOG:" $LOG
