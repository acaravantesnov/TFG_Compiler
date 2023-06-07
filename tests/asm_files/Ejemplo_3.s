addi x18, x0, 80
addi x19, x0, 100
addi x18, x18, 1
bne x18, x19, -4
addi x7, x0, 255
lui x20, 1
sb x7, 2(x20)
sb x18, 0(x20)