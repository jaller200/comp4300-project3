.text
main:
    add     $1, $2, $3
    addi    $1, $2, 0x1000
    b       main
    beq     $1, $2, main
    beqz    $1, main
    bge     $1, $2, main
    bne     $1, $2, main
    nop
    subi    $1, $2, 0x1000
    syscall