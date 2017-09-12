// Java no hace la optimizacion de la llamada a la cola

public class recursion
{
    public static void main(String []args)
    {
        mario(10);
    }

    static int mario(int x)
    {
        if (x == 0)
        {
            return 1/x;
        }
        else
        {
            return mario(x-1);
        }
    }
}