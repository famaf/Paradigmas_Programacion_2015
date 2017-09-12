object alto_orden
{
    def main(args: Array[String])
    {
        val y = () => { println ("no lazy") ; 10} 
        println (y())
        println (y())

        lazy val x = { println ("lazy") ; 5}
        println (x)
        println (x)   
        println ()

    }
}