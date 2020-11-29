.text
main:
    la      $a0, test
    li      $v1, 1024
    li      $v0, 8
    syscall

    li      $v0, 4
    syscall

    li      $v0, 10
    syscall

.data
test:   .space 1024
