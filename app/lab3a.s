.text
main:
    li      $2, 0
    li      $3, 32

loop:
    subi    $3, $3, 1
    nop
    nop
    nop
    nop
    nop
    bge     $3, $2, loop
    nop

    li      $2, 10
    syscall