// En Java el pasaje de parametros es por VALOR
// Pero cuando en el metodo Point, modificamos sus atributos, haciendo que estos tengan nuevos valores.
// Es decir que modificamos la referencia a esa variable.

public class Point
{
    public int x;
    public int y;
    
    public Point(int x, int y)
    {
        System.out.println("----------------------------");
        System.out.println("POINT");
        this.x = x; // PASAJE POR Referencia, porque
        this.y = y;
        System.out.println("this.x = " + this.x);
        System.out.println("this.y = " + this.y);
        System.out.println("----------------------------");
    }

    // Intercambio de variables (Swap).
    // Tanto el x como el y de arg1 valen 100
    // arg2 va a tener lo que tiene arg1

    // Como el pasaje de parametros de Java es por valor, tanto arg1 y arg2, son copias
    // por lo que sus valore NO se modificaran al final del metodo
    public static void tricky1(Point arg1, Point arg2)
    {
        System.out.println("----------------------------");
        System.out.println("TRICKY_1");
        arg1.x = 100; // Aca si cambia el valor de 'x' porque accedo a los campos de arg1 (que es un Point)
        arg1.y = 100; // Aca si cambia el valor de 'y' porque accedo a los campos de arg1 (que es un Point)
        System.out.println("arg1 = " + arg1 + "y arg2 = " + arg2);
        System.out.println("-----");
        Point temp = arg1;
        System.out.println("temp = " + temp);
        arg1 = arg2;
        System.out.println("arg1 = " + arg1);
        arg2 = temp;
        System.out.println("arg2 = " + arg2);
        System.out.println("----------------------------");
    }


    public static void tricky2(Point arg1, Point arg2)
    {
        System.out.println("----------------------------");
        System.out.println("TRICKY_2");
        arg1 = null;
        System.out.println("arg1 = " + arg1);
        arg2 = null;
        System.out.println("arg2 = " + arg2);
        System.out.println("----------------------------");
    }


    public static void main(String [] args)
    {
        Point pnt1 = new Point(0,0); // x = 0, y = 0
        Point pnt2 = new Point(0,0); // x = 0, y = 0
        
        System.out.println("\npnt1 X: " + pnt1.x + " pnt1 Y: " +pnt1.y);
        System.out.println("pnt2 X: " + pnt2.x + " pnt2 Y: " +pnt2.y);

        System.out.println("\ntriki1");
        tricky1(pnt1,pnt2);
        System.out.println("pnt1 X: " + pnt1.x + " pnt1 Y:" + pnt1.y);
        System.out.println("pnt2 X: " + pnt2.x + " pnt2 Y: " +pnt2.y);
        
        System.out.println("\ntriki2");
        tricky2(pnt1,pnt2);
        System.out.println("pnt1 X: " + pnt1.x + " pnt1 Y:" + pnt1.y);
        System.out.println("pnt2 X: " + pnt2.x + " pnt2 Y: " +pnt2.y + "\n");
    }
}
