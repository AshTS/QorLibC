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
.globl sys_read
sys_read:
    li a7, 0
    ecall
    ret

.section .text.write
.globl sys_write
sys_write:
    li a7, 1
    ecall
    ret

.section .text.open
.globl sys_open
sys_open:
    li a7, 2
    ecall
    ret

.section .text.close
.globl sys_close
sys_close:
    li a7, 3
    ecall
    ret

.section .text.lseek
.globl sys_lseek
sys_lseek:
    li a7, 8
    ecall
    ret

.section .text.mmap
.globl sys_mmap
sys_mmap:
    li a7, 9
    ecall
    ret

.section .text.munmap
.globl sys_munmap
sys_munmap:
    li a7, 11
    ecall
    ret

.section .text.sigaction
.globl sys_sigaction
sys_sigaction:
    li a7, 13
    ecall
    ret

.section .text.sigreturn
.globl sys_sigreturn
sys_sigreturn:
    li a7, 15
    ecall
    ret

.section .text.ioctl
.globl sys_ioctl
sys_ioctl:
    li a7, 16
    ecall
    ret

.section .text.pipe
.globl sys_pipe
sys_pipe:
    li a7, 22
    ecall
    ret

.section .text.dup
.globl sys_dup
sys_dup:
    li a7, 32
    ecall
    ret

.section .text.dup2
.globl sys_dup2
sys_dup2:
    li a7, 33
    ecall
    ret

.section .text.pause
.globl sys_pause
sys_pause:
    li a7, 34
    ecall
    ret

.section .text.nanosleep
.globl sys_nanosleep
sys_nanosleep:
    li a7, 35
    ecall
    ret

.section .text.getpid
.globl sys_getpid
sys_getpid:
    li a7, 39
    ecall
    ret

.section .text.fork
.globl sys_fork
sys_fork:
    li a7, 57
    ecall
    ret

.section .text.execve
.globl sys_execve
sys_execve:
    li a7, 59
    ecall
    ret

.section .text.exit
.globl sys_exit
sys_exit:
    li a7, 60
    ecall
    exit_loop:
    j exit_loop

.section .text.wait
.globl sys_wait
sys_wait:
    li a7, 61
    ecall
    ret

.section .text.kill
.globl sys_kill
sys_kill:
    li a7, 62
    ecall
    ret

.section .text.getdents
.globl sys_getdents
sys_getdents:
    li a7, 78
    ecall
    ret

.section .text.getcwd
.globl sys_getcwd
sys_getcwd:
    li a7, 79
    ecall
    ret

.section .text.chdir
.globl sys_chdir
sys_chdir:
    li a7, 80
    ecall
    ret

.section .text.mkdir
.globl sys_mkdir
sys_mkdir:
    li a7, 83
    ecall
    ret

.section .text.rmdir
.globl sys_rmdir
sys_rmdir:
    li a7, 84
    ecall
    ret

.section .text.unlink
.globl sys_unlink
sys_unlink:
    li a7, 87
    ecall
    ret

.section .text.setpgid
.globl sys_setpgid
sys_setpgid:
    li a7, 109
    ecall
    ret


.section .text.sync
.globl sys_sync
sys_sync:
    li a7, 162
    ecall
    ret

.section .text.reboot
.globl sys_reboot
sys_reboot:
    li a7, 169
    ecall
    ret