public class alcance
{
    static int a = 5;

    public static int g()
    {
        return a;
    }

    public static void main(String []args)
    {
        int a = 0;
        int b = g();
        System.out.println("b vale: " + b);
    }
}