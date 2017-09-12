// SCALA SI TIENE OPTIMIZACION DE LA RECURSION A LA COLA

object recursion
{
    def main(args: Array[String])
    {
        var x = 1 // Cambiar por x = 1, si se quiere ver como seria el stack un solo bloques
        try
        {
            if (x == 1) f(10) else g(10)
        }
        catch 
        {
          case e: Exception => e.printStackTrace()
        }
    }

    // Funcion Recursiva,tendria que tener 1 bloque f
    def f(n : Int)
    {
        if (n == 0) 1/0 else f(n-1)
    }

    // Funcion NO Recuersiva, tendria que tener 10 bloques g
    def g(n : Int): Int =
    {
        if (n == 0) 1/0 else 1 + g(n-1)
    }
}