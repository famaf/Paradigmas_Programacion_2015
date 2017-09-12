# Python NO tiene optimizacion en la llamadaa a la cola

# Si tuviera la optimizacion a la cola, mostraria un solo bloque y no varios

def g(n):
    if n == 0: return 1/0
    else: return g(n-1)


g(10)
