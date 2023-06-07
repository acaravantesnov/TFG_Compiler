addi x2, x0, 256
addi x6, x0, 324
addi x7, x6, -400
sb x6, 0(x2)
sb x7, 1(x2)
lw x6, 0(x2)
lw x7, 1(x2)
slt x18, x6, x7