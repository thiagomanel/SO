%define SYSCALL_WRITE 0x2000004
%define SYSCALL_EXIT  0x2000001

;sycall number is passed in register %rax.
;rdi - used to pass 1st argument to functions
;rsi - used to pass 2nd argument to functions
;rdx - used to pass 3rd argument to functions
;rcx - used to pass 4th argument to functions
;r8 - used to pass 5th argument to functions
;r9 - used to pass 6th argument to functions

global start
start:
  mov rdi, 1
  mov rsi, str
  mov rdx, strlen
  mov rax, SYSCALL_WRITE
  syscall

  mov rax, SYSCALL_EXIT
  mov rdi, 0
  syscall

section .data
str:
  db `Hello, assembly!\n` ; to use escape sequences, use backticks
strlen equ $ - str

