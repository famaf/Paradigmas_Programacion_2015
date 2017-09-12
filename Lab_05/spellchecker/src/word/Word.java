package word;

import java.lang.Object;

/**
 * Clase que representa una palabra.
*/
public class Word
{
	private String word; // Atributo	
	
	/**
	 * Crea una nueva palabra.
	 */
	public Word() // Constructor
	{
		word = new String();
	}
	
	/**
	 * Crea una nueva palabra con el String dado.
	 * @param palabra nueva a crear.
	 */
	public Word(String w) // Constructor
	{
		word = new String(w);
	}
	
	/**
	 * Asigna el String pasado a la varible word.
	 * 
	 * @param String que se quiere asignar.
	 */
	public void setWord(String w)
	{
		this.word= w;
	}
	
	/**
	 * Devuelve una palabra.
	 * @return Una Palabra.
	 */
	public String getWord()
	{
		return word;
	}
	
	/**
	 * Devuelve el HashCode de una palabra.
	 */
	public int hashCode()
	{
		final int prime = 31;
		int result = 1;
		result = prime * result + ((word == null) ? 0 : word.hashCode());
		return result;
	}

	/**
	 * Se fija si dos palabras son iguales.
	 */
	public boolean equals(Object obj)
	{
		if (this == obj)
		{
			return true;
		}
		
		if (obj == null)
		{
			return false;
		}
		
		if (!(obj instanceof Word))
		{
			return false;
		}
		
		Word other = (Word) obj;
		
		if (word == null)
		{
			if (other.word != null)
			{
				return false;
			}
		}
		else if (!word.equals(other.word))
		{
			return false;
		}
		
		return true;
	}
}
