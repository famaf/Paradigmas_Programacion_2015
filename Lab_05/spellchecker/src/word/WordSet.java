package word;

import java.util.Iterator;
import java.util.HashSet;
import word.Word;

/**
 * Clase que representa un conjunto de palabras.
 */
public class WordSet
{
	private HashSet<Word> set;

	/**
	 * Crea un conjunto de palabras.
	 */
	public WordSet() // Constructor
	{
		set = new HashSet<Word>();
	}
	
	/**
	 * Agrega una nueva palabra al conjunto.
	 * @param Una palabra.
	 */
	public void add(Word new_word)
	{
		set.add(new_word);
	}
	
	/**
	 * Se fija si la palabra esta en el conjunto.
	 * @param Una palabra.
	 * @return True si esta o False sino.
	 */
	public boolean contains(Word new_word)
	{
		return set.contains(new_word);
	}
	
	/**
	 * Elimina el conjunto de palabras.
	 */
	public void clear()
	{
		set.clear();
	}
	
	/**
	 * Itera sobre el conjunto de palabras.
	 * @return Referencia al iterador del conjunto.
	 */
	public Iterator<Word> iterator()
	{
		Iterator<Word> iter = set.iterator();
		return iter;
	}
	
	/**
	 * Calcula el tamaño del conjunto de palabras.
	 * @return El tamaño del conjunto.
	 */
	public int size()
	{
		return set.size();
	}
}
