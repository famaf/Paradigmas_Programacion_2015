package dictionary;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.io.FileReader;

/**
 * Representa un diccionario que se carga desde un archivo.
 */
public class FileDictionary extends Dictionary
{
	private String loadPath;
	
	/**
	 * Crea un archivo diccionario por defecto
	 * llamado "dict.txt".
	 */
	public FileDictionary() // Constructor
	{
		super();
		this.loadPath = "dict.txt";
		this.load(loadPath);
	}
	
	/**
	 * Crea un archivo diccionario apartir de la ruta dada.
	 * @param Ruta del diccionario.
	 */
	public FileDictionary(String filepath) // Constructor
	{
		super();
		this.loadPath = filepath;
		this.load(loadPath);
	}
	
	/**
	 * Carga el diccionario desde un archivo.
	 * @param Ruta de donde se cargara el diccionario.
	 */
	public void load(String filepath)
	{
		try
		{
			BufferedReader bf = new BufferedReader(new FileReader(filepath));
			String sCadena;
			List<String> lista = new ArrayList<String>();
		
			while ((sCadena = bf.readLine()) != null) 
			{
				lista.add(sCadena);
			}
		
			fromStringList(lista);
		
			bf.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
	
	/**
	 * Guarda un diccionario en un archivo, del cual se cargo.
	 * @throws IOException
	 */
	public void save() throws IOException
	{
		save(this.loadPath);
	}
	
	/**
	 * Guarda un diccionario en la dirreccion indicada.
	 * @param Ruta donde se guardara el archivo.
	 * @throws IOException
	 */
	public void save(String filepath) throws IOException
	{
		BufferedWriter bf = new BufferedWriter(new FileWriter(filepath));
		
		List<String> lista = new ArrayList<String>();
		
		lista = toStringList();
		
		Iterator<String> it = lista.iterator();
		
		while(it.hasNext())
		{
			bf.write(it.next()+"\n");
		}
		
		bf.close();				
	}
}
