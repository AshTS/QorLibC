.globl main
.globl exit

.globl _start
_start:

    call main
    call exit
2:
    j 2b