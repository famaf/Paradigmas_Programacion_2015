#!/bin/bash

# Agregamos palabra al diccionario principal
function dict_add 
{
    echo $1 >> $2
}

# Agregamos palabra al diccionario de palabras ignoradas
function ignored_add
{
    echo $1 >> "dict_ignored"
}

# Destruimos el archivo de salida: out.txt
# Para escribir en uno nuevo
function out_destroy
{
    FILE=out.txt
    if [ -e $FILE ]; then
        rm -f "out.txt"
    fi
}

# Destruyo el diccionario de palabras ignoradas
function destroy_ignored
{
    rm -f dict_ignored
}


# Toma una palabra y los dos diccionario y se fija si existe en dichos diccionarios
# Si existe ==> TRUE
# Si no ==> FALSE
function is_know
{
    # Flags:
       # * q : No me muestra las coincidencias
       # * x : Me compara las palabra, no si la contiene adentro (revisar)
    grep -q -x $1 $2 dict_ignored # Me devuelve 1 Si no Existe y 0 si Existe
                               # Me guarda el resultado en '$?'
    if [ $? -eq 0 ]; then
        echo "TRUE"
    else
        echo "FALSE"
    fi
}

# Consulta al usuario de que accion desea realizar con la palabra que no es
# conocida. Aceptar, Ignorar, Reemplazar.
function consult_user
{
    echo "Palabra no reconocida <$palabra>: Aceptar (a) - Ignorar (i) - Reemplazar (r): "
    local new_word
    read opcion < /dev/tty
    if [ "$opcion" == 'a' ]; then
        dict_add $palabra $2
        printf "%s" "$palabra" >> out.txt
    elif [ "$opcion" == 'i' ]; then
        echo $palabra >> "dict_ignored"
        printf "%s" "$palabra" >> out.txt
    elif [ "$opcion" == 'r' ]; then
        echo "Ingrese la palabra por la cual quiere reemplazar <$palabra> : "
        read new_word < /dev/tty
        printf "%s" "$new_word" >> out.txt
    else
        echo -e "Opcion incorrecta !!!\nPorfavor ingrese una opcion valida."
        consult_user $palabra
    fi
}

# Procesa el documento de entrada linea por linea
function process_document
{
    while IFS= read line; do
        for word in $line; do
            word_len=${#word}  # Tamaño de la palabra
            pref_len=`expr "$word" : '[^[:alpha:]]*'`  # Tamaño del prefijo
            prefijo=${word:0:pref_len}  # Prefijo
            palabra_len=`expr "${word:pref_len}" : '[[:alpha:]]*'`  # Tamaño de la palabra sin prefijo ni sufijo
            palabra=${word:pref_len:palabra_len}  # Palabra sin prefijo ni sufijo
            suf_starts=$(($pref_len+$palabra_len))  # Desde donde empieza del sufijo (suma el tamaño del prefijo y la de la palabra)
            sufijo=${word:suf_starts}  # Sufijo

            printf "%s" "$prefijo" >> out.txt  # Copio el prefijo al documento de salida

            # Si la palabra existe la copio al
            if [ `is_know $palabra $2` == "TRUE" ]; then
                printf "%s" "$palabra" >> out.txt  # Copio la palabra al documento de salida en caso de que sea conocida
            else
                consult_user $palabra $2  # Consulto por la palabra desconocida
            fi
            printf "%s" "$sufijo " >> out.txt  # Copio el prefijo al documento de salida con espacios Hardcodeados
        done
        printf "\n" >> out.txt  # Salto de linea por cada linea
    done < $1
}


function main
{
    out_destroy

    # Numero de argumento erroreos
    if [[ $#<1 ]]; then
        echo "spellchecker.sh: Nro de argumentos erroneo. Deben ser <documento> [<diccionario>]."
        exit 1
    fi
    
    touch dict_ignored # Creo diccionario de palabras ignoradas
    if [[ $#<2 ]]; then # En caso de que no se  haya ingresado diccionario busco un "dict.txt" por defecto
                        # Si no lo encuentro creo un "dict.txt"
        FILE=dict.txt
        if [ -e $FILE ]; then
            diccionario=dict.txt
            process_document $1 $diccionario
        else
            echo -e "No se especifico diccionario, entonces creamos un archivo 'dict.txt'\n"
            touch dict.txt
            diccionario=dict.txt
            process_document $1 $diccionario # Procesamos el documento de entrada con el diccionario especificado
        fi
    else # La entrada contiene el diccionario, es decir, se ingreso el diccionario
        process_document $1 $2
    fi
    echo "El documento <$1> ha sido procesado. Resultados en <out.txt>"

    destroy_ignored
}

main $1 $2  # Inicio de programa

