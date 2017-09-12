x = 200


def alcance(n):
    def g(n):
        return x + n
    return g(n)

x = 3
z = alcance(0)
print(z)
