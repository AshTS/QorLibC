.section .text.syscall
.globl syscall
syscall:
    mv a7, a0
    mv a0, a1
    mv a1, a2
    mv a2, a3
    mv a3, a4
    mv a4, a5
    mv a5, a6
    ecall
    ret

.section .text.read
.globl read
read:
    li a7, 0
    ecall
    ret

.section .text.write
.globl write
write:
    li a7, 1
    ecall
    ret

.section .text.open
.globl open
open:
    li a7, 2
    ecall
    ret

.section .text.close
.globl close
close:
    li a7, 3
    ecall
    ret

.section .text.lseek
.globl lseek
lseek:
    li a7, 8
    ecall
    ret

.section .text.mmap
.globl mmap
mmap:
    li a7, 9
    ecall
    ret

.section .text.munmap
.globl munmap
munmap:
    li a7, 11
    ecall
    ret

.section .text.sigaction
.globl sigaction
sigaction:
    li a7, 13
    ecall
    ret

.section .text.sigreturn
.globl sigreturn
sigreturn:
    li a7, 15
    ecall
    ret

.section .text.ioctl
.globl ioctl
ioctl:
    li a7, 16
    ecall
    ret

.section .text.pipe
.globl pipe
pipe:
    li a7, 22
    ecall
    ret

.section .text.dup
.globl dup
dup:
    li a7, 32
    ecall
    ret

.section .text.dup2
.globl dup2
dup2:
    li a7, 33
    ecall
    ret

.section .text.pause
.globl pause
pause:
    li a7, 34
    ecall
    ret

.section .text.nanosleep
.globl nanosleep
nanosleep:
    li a7, 35
    ecall
    ret

.section .text.fork
.globl fork
fork:
    li a7, 57
    ecall
    ret

.section .text.execve
.globl execve
execve:
    li a7, 59
    ecall
    ret

.section .text.exit
.globl exit
exit:
    li a7, 60
    ecall
    exit_loop:
    j exit_loop

.section .text.wait
.globl wait
wait:
    li a7, 61
    ecall
    ret

.section .text.kill
.globl kill
kill:
    li a7, 62
    ecall
    ret

.section .text.getdents
.globl getdents
getdents:
    li a7, 78
    ecall
    ret

.section .text.getcwd
.globl getcwd
getcwd:
    li a7, 79
    ecall
    ret

.section .text.chdir
.globl chdir
chdir:
    li a7, 80
    ecall
    ret

.section .text.mkdir
.globl mkdir
mkdir:
    li a7, 83
    ecall
    ret

.section .text.sync
.globl sync
sync:
    li a7, 162
    ecall
    ret