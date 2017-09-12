import java.io.IOException;
import dictionary.Dictionary;
import dictionary.MemDictionary;
import dictionary.FileDictionary;
import word.Word;
import document.Document;
import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Esta clase implementa la aplicacion Spellchecker
 * (Corrector Ortografico) la cual toma un documento y analiza
 * palabra por palabra, consultando al usuario si se desconoce
 * una palabra, para tomar una decision sobre esa palabra.
 */
public class Spellchecker
{
    public static void main(String[] args)
    {
        if (args.length < 2)
        {
            System.out.println("Spellchecker.java: Nro de argumentos erroneo. Deben ser <documento> [<diccionario>].");
        }
        else
        {
            
            FileDictionary dict_main = new FileDictionary(args[1]);
            
            MemDictionary dict_ignored = new MemDictionary();
            
            processDocument(args[0], "out.txt", dict_main, dict_ignored);
            
            try
            {
                dict_main.save();
                dict_ignored.clear();
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
            
            System.out.println("El documento '" + args[1] + "' ha sido procesado. Resultados en 'out.txt'\n");
        }   
    }
    
    /**
     * Constructor Spellchecker. 
     */
    public Spellchecker()
    {
    	
    }
    
    /**
     * Decide que hacer frente a una palabra desconocida.
     * @param Palabra.
     * @param Diccionario Principal.
     * @param Diccionario de palabras ignoradas (se crea solo).
     * @return Palabra a colocar en el documento de salida.
     * @throws IOException
     */
    public static Word consultUser(Word word, Dictionary dict_main, Dictionary dict_ignored) throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
  
        System.out.print("Palabra no reconocida: " + "<" + word.getWord() + ">" +" Aceptar (a) - Ignorar (i) - Reemplazar (r): ");
        String opcion = reader.readLine();
        
        if(opcion.equals("a"))
        {
            dict_main.add(word);
        }
        else if(opcion.equals("i"))
        {
            dict_ignored.add(word);
        }
        else if(opcion.equals("r"))
        {
            System.out.print("Ingrese la palabra por la cual quiere reemplazar"+" <"+word.getWord()+"> "+": ");
            word.setWord(reader.readLine());
        }
        else
        {
            System.out.print("La opcion "+"<"+opcion+">"+" es incorrecta. Por favor ingrese una opción válida. \n");
            consultUser(word, dict_main, dict_ignored);
        }
        
        return word;
    }
    
    /**
     * Analiza el documento de entrada, y modifica el diccionario principal
     * y el documento de salida dependiendo de las elecciones del usuario.
     * @param Documento de entrada.
     * @param Documento de salida.
     * @param Diccionario principal.
     * @param Diccionario de palabras ignoradas.
     */
    public static void processDocument(String word_1, String word_2, Dictionary dict_main, Dictionary dict_ignored)
    {
        Document doc = new Document(word_1, word_2);
        
        Word next_word;
        
        while((next_word = doc.getWord()) != null)
        {
        
            if (!(dict_main.contains(next_word) || dict_ignored.contains(next_word)))
            {
                try
                {
					consultUser(next_word, dict_main, dict_ignored);
				}
                catch (IOException e)
                {
					e.printStackTrace();
				}
            }
        
            doc.putWord(next_word);
        
        }
        
        doc.close();
    }
}