object alcance
{
    def main(args: Array[String])
    {
        var a : Int = g()
        println(a)
    }
    var x = 2
    def f(): Int ={
        return x
    }
    
    def g(): Int ={
        var x = 3
        return f()
    }
}