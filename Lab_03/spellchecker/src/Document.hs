{-# LANGUAGE DoAndIfThenElse #-}

module Document (Document, Word, doc_open, doc_close, doc_get_word, doc_put_word) where

import qualified Data.Char as Char
import System.IO
import System.IO.Error

type Word = String
type Document = (Handle, Handle)

-- | Abre los archivos especificados por los paths
--   pasados como argumentos. El primer path repre-
--   senta el archivo de entrada a procesar, y el
--   segundo path representa el archivo de salida
--   donde se guarda el documento ya procesado.
doc_open :: FilePath -> FilePath -> IO Document
doc_open in_path out_path = do
                            handle_in <- openFile in_path ReadMode
                            handle_out <- openFile out_path WriteMode
                            return (handle_in, handle_out)


-- | Cierra los archivos especificados -- hClose:: Handle -> IO ()
doc_close :: Document -> IO ()
doc_close documento = let doc_in = fst(documento)
                          doc_out = snd(documento)
                      in
                          do
                          hClose doc_in 
                          hClose doc_out


-- | Obtiene una palabra del documento especificado,
--   copiando todos los caracteres no alfabeticos
--   precedentes al archivo de salida.
--   Cuando alcanza el final del documento, lo señaliza
--   con una excepcion.
doc_get_word :: Document -> IO Word
doc_get_word documento = doc_get_word_2 documento []


doc_get_word_2 :: Document -> [Char] -> IO Word
doc_get_word_2 documento [] = let doc_in = fst(documento)
                                  doc_out = snd(documento)
                              in
                              do
                              caracter <- hGetChar doc_in
                              if Char.isAlpha caracter then
                                  doc_get_word_2 documento [caracter]
                              else 
                                  do
                                  hPutChar doc_out caracter
                                  doc_get_word_2 documento []

doc_get_word_2 documento xs = let doc_in = fst(documento) in
                              
                catchIOError (do
                              caracter <- hGetChar doc_in
                              if Char.isAlpha caracter then
                                  doc_get_word_2 documento (xs++[caracter])
                              else
                                  do 
                                  hSeek doc_in RelativeSeek (-1)
                                  return xs
                              )
                (\e -> return xs)


-- | Escribe una palabra en el documento de salida. -- hPutStr :: Handle -> String -> IO ()
doc_put_word :: Word -> Document -> IO ()
doc_put_word palabra documento = let doc_out = snd(documento)
                                 in
                                    hPutStr doc_out palabra
