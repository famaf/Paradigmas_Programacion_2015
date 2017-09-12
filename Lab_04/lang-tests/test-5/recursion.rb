# Ruby no tiene optimizacion de llamada a la cola

def g(n)
    if n == 0
        1/n
    else
        g(n-1)
    end
end


g(10)
