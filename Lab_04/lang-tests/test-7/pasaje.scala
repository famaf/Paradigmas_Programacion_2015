object Pasaje
{
    def main(args: Array[String])
    {
        val x = 10
        val y = 100

        call_by_value ({println ("HOLA"); x})

        call_by_name ({println ("CHAU"); y})
    }

    /*
        Al llamar a call_by_value (Al ser por Valor), lo primero que hace es Imprimir
            HOLA
            AGUA
            10
        Porque ejecuta el parametro pasado a la funcion, en el orden adecuado y despues
        el cuerpo de la funcion llamada
    */
    def call_by_value (x: Int)
    {
        println("AGUA")
        println(x)
        println("\n")
    }


    /*
        Al llamar a call_by_name (Al ser por Nombre), lo primero que hace es Imprimir
            FUEGO
            CHAU
            100
        Porque ejecuta el parametro pasado a la funcion, cuando lo necesita por lo que cualquier
        print anterior a la llamada a la varible pasada como argumento, y cuando llega al usar la
        variable propia de la funcion, ejecuta lo pasado a dicha funcion cuando se llama
    */
    def call_by_name (y: => Int) // => : hace que sea pasaje por nombre en vez de por valor (por defecto en scala)
    {
        println("FUEGO")
        println(y)
        println("\n")
    }


}
