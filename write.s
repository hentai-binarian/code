.global _start
.intel_syntax noprefix
_start:
  push rbp
  mov rbp, rsp
  sub rsp, 0x8
  mov QWORD PTR [rsp], 0x41   ; 文字列"A"
  mov rax, 1                  ; write()で画面に出力
  mov rdx, 8                
  mov rdi, 1
  mov rsi, rsp
  syscall

  mov rax, 60
  syscall
