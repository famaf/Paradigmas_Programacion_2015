package dictionary;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import word.WordSet;
import word.Word;

/**
 * Crea un diccionario abstracto apartir de 
 * un conjunto de palabras.
 */
public abstract class Dictionary
{
	protected WordSet set;
	
	/**
	 * Crea un Diccionario.
	 */
	public Dictionary() // Constructor
	{
		set = new WordSet();
	}
	
	/**
	 * Agrega una palabra al diccionario.
	 * @param Palabra.
	 */
	public void add(Word new_word)
	{
		set.add(new_word);
	}
	
	/**
	 * Se fija si una palabra esta en el diccionario.
	 * @param Palabra.
	 * @return True si la palabra esta o False sino.
	 */
	public boolean contains(Word new_word)
	{
		return set.contains(new_word);
	}
	
	/**
	 * Elimina el diccionario.
	 */
	public void clear()
	{
		set.clear();
	}
	
	/**
	 * Inserta en el diccionario los elementos de la lista de palabras.
	 * @param Lista de palabras
	 */
	public void fromStringList(List<String> lista)
	{
		Iterator<String> it = lista.iterator();
		
		
		while(it.hasNext())
		{
			Word word = new Word(it.next());
			set.add(word);
		}		
	}
	
	/**
	 * Devuelve una lista de palabras que pertenecen al diccionario.
	 * @return Lista de palabras.
	 */
	public List<String> toStringList()
	{
		
		List<String> lista = new ArrayList<String>();
		Iterator<Word> it = set.iterator();
		
		while(it.hasNext())
		{
			lista.add(it.next().getWord());
		}
		
		return lista;
	}
	
	/**
	 * Calcula el tamaño del diccionario.
	 * @return El tamaño del diccionario.
	 */
	public int size()
	{
		return set.size();
	}
}
