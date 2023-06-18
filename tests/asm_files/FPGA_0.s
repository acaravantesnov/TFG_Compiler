lui x20, 1
lui x21, 16
addi x21, x21, -1
sh x21, 2(x20)
lw x22, 1(x20)
sw x22, 0(x20)
jal x23, -12