{-# LANGUAGE DoAndIfThenElse #-}
-- |

module SpellChecker (do_spellcheck) where

import System.IO.Error
import Data.List.Split
import Dictionary
import Document
import CommandLine

-- | La funcion 'do_spellcheck' es la funcion que se encarga de manejar
--   el proceso de chequeo ortografico. Esto incluye, cargar el diccionario,
--   abrir el archivo a procesar, procesar el archivo y luego guardar el
--   diccionario y el archivo de entrada ya procesado.
--   Toma como argumento los argumentos de linea de comando de tipo 'Params'.
do_spellcheck :: Params -> IO ()
do_spellcheck params = let
                           filepath = (filename params)
                           dict = (dictionary params)
                           dict_ignored = dict_new
                           name_doc_in = get_name_from_file filepath
                       in
                       do
                           dict_main <- dict_load dict
                           doc <- doc_open filepath "out.txt"
                           dict_procesado <- process_document doc dict_main dict_ignored
                           doc_close doc
                           dict_save dict dict_procesado
                           putStrLn ("\nEl documento '" ++ name_doc_in ++ "' ha sido procesado con exito. \nResultados en 'out.txt'")


get_name_from_file :: String -> String
get_name_from_file filepath = last(splitOn "/" filepath)

-- | La funcion 'process_document' ejecuta el proceso de chequeo ortografico.
--   Para ello, procesa el archivo palabra por palabra, copiandolas al archivo
--   de salida y consultando al usuario sobre que accion realizar ante una
--   palabra desconocida.
--   Cuando se termina de procesar el archivo, lo cual es señalizado mediante
--   una excepcion por 'doc_get_word', retorna el diccionario (el cual puede
--   haber sido modificado) para guardarlo.
process_document :: Document -> Dictionary -> Dictionary -> IO Dictionary
process_document doc dict_main dict_ignored = 
                                catchIOError (do
                                              word <- doc_get_word doc
                                              if is_word_known word dict_main dict_ignored then
                                                  do
                                                  doc_put_word word doc
                                                  dict_main <- process_document doc dict_main dict_ignored
                                                  return dict_main
                                              else
                                                  do
                                                  (word_tmp, dict_main_tmp, dict_ignored_tmp) <- consult_user word dict_main dict_ignored
                                                  doc_put_word word_tmp doc
                                                  dict_main_tmp <- process_document doc dict_main_tmp dict_ignored_tmp
                                                  return dict_main_tmp
                                              )
                                (\e -> return dict_main)


is_word_known :: Word -> Dictionary -> Dictionary -> Bool
is_word_known word dict_1 dict_2 = (dict_contains word dict_1) || (dict_contains word dict_2)

-- | Verifica si una palabra es conocida, en cuyo caso, continua
--   con el procesamiento del archivo, sin realizar ninguna accion.
--   Si la palabra no es conocida, pregunta al usuario que accion
--   realizar con la misma. Las acciones pueden ser aceptar, ignorar
--   o reemplazar.
consult_user ::  Word -> Dictionary -> Dictionary -> IO (Word, Dictionary, Dictionary)
consult_user word dict_main dict_ignored = do
                                           putStrLn ("\nPalabra no reconocida: '" ++ word ++ "'")
                                           putStrLn ("Aceptar(a) - Ignorar(i) - Remplazar(r)")
                                           choice <- getLine

                                           case choice of "a" -> return(word, (dict_add word dict_main), dict_ignored)
                                                          "i" -> return(word, dict_main ,(dict_add word dict_ignored))
                                                          "r" -> do
                                                                 putStrLn ("Ingrese la palabra por la cual quiere reemplazar '" ++ word ++ "': ")
                                                                 new_word <- getLine
                                                                 return (new_word, dict_main, dict_ignored)
                                                          (_) -> do
                                                                 putStrLn("\nLa opcion [" ++ choice ++ "] es invalida, porfavor ingrese una opcion valida")
                                                                 consult_user word dict_main dict_ignored
