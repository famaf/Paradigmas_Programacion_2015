# El pasaje de parametros de Perl es por REFERENCIA

$x = 50;
$y = 70;

print "\nANTES DE INTERCHANGE: x = $x, y = $y\n";

&interchange ($x, $y);

print "\nDESPUES DE INTERCHANGE: x = $x, y = $y\n\n";


sub interchange
{
    ($x1, $y1) = @_; # x1 e y1 son variables locales que toman x e y respectivamente

    @_[0] = $y1;

    @_[1] = $x1;

    #print "\nADENTRO DE INTERCHANGE (ARREGLO): x1 = @_[0], y1 = @_[1]\n"
    print "\nADENTRO DE INTERCHANGE (VALORES): x1 = $x1, y1 = $y1\n"

}