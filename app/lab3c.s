.text
main:
    li      $6, 0
    li      $7, 10
    li      $8, 100
    li      $9, 1000
    li      $10, 7

loop:
    subi    $10, $10, 1
    add     $6, $6, $7
    add     $6, $6, $8
    add     $6, $6, $9
    bge     $10, $0, loop
    nop

    add     $4, $0, $6
    li      $2, 1
    syscall

    li      $2, 10
    syscall


