.globl main
.globl exit
.globl environ

.globl _start
_start:
    la t0, environ
    sd a2, 0(t0)
    call main
    call exit
2:
    j 2b