package document;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import word.Word;
import java.lang.Character;

/**
 * Representa el documento que se va a procesar.
 * 
 */
public class Document
{	
	private BufferedReader input;
	
	private BufferedWriter output;
	
	/**
	 * Crea un documento que representa el documento
	 * de entrada y de salida.
	 * @param Documento de entrada.
	 * @param Documento de salida.
	 */
	public Document(String doc_in, String doc_out) // Constructor
	{
		try
		{
			input = new BufferedReader(new FileReader(doc_in));
		} 
		catch (FileNotFoundException e1)
		{
			e1.printStackTrace();
		}
		try 
		{
			output = new BufferedWriter(new FileWriter(doc_out));
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 * Cierra el documento de entrada y el de salida.
	 */
	public void close()
	{
		try
		{
			input.close();
			output.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
	
	/**
	 * Obtiene una palabra del documento de entrada.
	 * @return Palabra del documento.
	 */
	public Word getWord()
	{
		String string = "";
		Word word = new Word();
		try
		{
			input.mark(1);
			int c = input.read();
			
			while(!Character.isLetter((char) c))
			{
				if(c == -1)
				{
					return null;
				}
				output.write((char) c);
				c = input.read();
			}
			
			while(c != -1 && Character.isLetter((char) c))
			{
				string += (char) c;
				input.mark(1);
				c = input.read();
			}
			
			if(!Character.isLetter((char) c) && c != -1)
			{
				input.reset();
			}
			
			word.setWord(string);
			word.getWord();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		return word;
	}
	
	/**
	 * Coloca una palabra en el documento de salida.
	 * @param Palabra.
	 */
	public void putWord(Word palabra)
	{
		try
		{
			output.write(palabra.getWord());
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
}
