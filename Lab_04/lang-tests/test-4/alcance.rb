$x = 200

def alcance()
    return $x
end

def main()
    $x = 3
    z = alcance()
    puts z
end

main()