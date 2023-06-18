lui x20, 1
lui x21, 16
addi x21, x21, -1
sh x21, 2(x20) // TRI
lh x22, 1(x20) // DATOSIN
sh x22, 0(x20) // DATOSOUT
jal x23, -12