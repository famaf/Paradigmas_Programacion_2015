f = let x = 10 in (\z -> x + z)

g = let h = f
        x = 1
    in  show $ h 1