{-# LANGUAGE DoAndIfThenElse #-}

module Dictionary (Dictionary, dict_new, dict_add, dict_contains, dict_load, dict_save) where

import qualified Data.Set as Set
import System.IO
import System.IO.Error

type Word = String
type Dictionary = Set.Set Word


-- | Crea un nuevo diccionario vacio
dict_new :: Dictionary
dict_new = Set.empty


-- | Agrega una palabra al diccionario especificado
dict_add :: Word -> Dictionary -> Dictionary
dict_add word diccionario = Set.insert word diccionario


-- | Verifica la existencia de una palabra en el
--   diccionario especificado
dict_contains :: Word -> Dictionary -> Bool
dict_contains word diccionario = Set.member word diccionario


-- | Carga un diccionario desde un archivo especificado.
dict_load :: FilePath -> IO Dictionary
dict_load filepath = do
                     diccionario <- readFile filepath
                     return (Set.fromList $ lines diccionario)


-- | Guarda el diccionario en el archivo especificado
dict_save :: FilePath -> Dictionary -> IO ()
dict_save filepath diccionario = 
                   catchIOError (do
                                 writeFile filepath (unlines (Set.toList diccionario))
                                )
                   (\e -> return ())
