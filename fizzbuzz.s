.intel_syntax noprefix
.global main

.section .rodata    # ここに文字列
f:
    .ascii "Fizz\n"
b:
    .ascii "Buzz\n"
fb:
    .ascii "FizzBuzz\n"
n:
    .ascii "\n"

.section .text
main:
    push rbp
    mov rbp, rsp
    mov r13, 1 # 割られる数
    mov r14, 3 # 割る数3 
    mov r15, 5 # 割る数5
    jmp cmp_fizzbuzz

cmp_fizzbuzz:
    xor rdx, rdx
    mov rax, r13
    div r14
    cmp rdx, 0 
    jne cmp_buzz # fizzではない
    xor rdx, rdx
    mov rax, r13
    div r15
    cmp rdx, 0
    jne call_fizz # fizzだった
    call fizzbuzz # fizzbuzzだった
    jmp cmp_exit

call_fizz:
    call fizz
    jmp cmp_exit

cmp_buzz:
    xor rdx, rdx
    mov rax, r13
    div r15
    cmp rdx, 0
    jne number # fizzでもbuzzでもないなら数字を表示
    call buzz # buzzだった
    jmp cmp_exit

number:
    mov r12, r13
    add r12, 0x30
    mov rsi, r12
    call print
    lea rsi, [n]
    call print
    jmp cmp_exit

cmp_exit:
    cmp r13, 100
    je exit
    inc r13
    jmp cmp_fizzbuzz

# fizzbuzzと表示
fizzbuzz:     
    mov rax, 1
    mov rdi, 1
    lea rsi, [fb]
    mov rdx, 9
    syscall
    ret

# fizzと表示
fizz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [f]
    mov rdx, 5
    syscall
    ret

# buzzと表示
buzz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [b]
    mov rdx, 5
    syscall
    ret

# 数字を表示
print:
    mov rax, 1
    mov rdi, 1
    mov rdx, 1
    syscall
    ret

#プログラムを終了
exit:
    mov rdi, 0
    mov rax, 60
    syscall

