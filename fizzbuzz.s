.intel_syntax noprefix
.global main

.section .rodata    # ここに文字列
fizz:
    .ascii "Fizz\n"
buzz:
    .ascii "Buzz\n"
fizzbuzz:
    .ascii "FizzBuzz\n"
n:
    .ascii "\n"

.section .text
main:
    sub rsp, 2
    # 割る数３はr15
    # 割る数５はr14
    # レジスタ、メモリの初期化ダルい...😥
    mov r14, 5           
    mov r15, 3          
    xor rax, rax
    xor rcx, rcx
    mov QWORD PTR [rsp], rax
    mov BYTE PTR [rsp], 1   # 割られる数
    mov rcx, 1
.loop:
    xor rdx, rdx            # rdxを初期化
    xor rax, rax            # raxを初期化
    mov al, BYTE PTR [rsp]
    div r15
    cmp rdx, 0
    jz .fizz_yes            # fizzであった場合
    xor rax, rax
    xor rdx, rdx
    mov al, BYTE PTR [rsp]
    div r14
    cmp rdx, 0
    jz .b                   # buzz
    xor rax, rax
    mov al, BYTE PTR [rsp]
    mov BYTE PTR [rsp+1], al
    add BYTE PTR [rsp+1], 0x30
    lea rsi, [rsp+1]
    call .write              # 数字を表示
    lea rsi, [rip+n]
    call .write              # 改行
    inc BYTE PTR [rsp]       # インクリメント 
    cmp BYTE PTR [rsp], 0x10
    jz .shift
.cmp:
    inc rcx
    cmp rcx, 100
    jz .exit
    jmp .loop                # 最初にもどる
.shift:
    shr BYTE PTR [rsp], 4
    jmp .cmp    
.fizz_yes:
    xor rdx, rdx    
    xor rax, rax   
    mov al, BYTE PTR [rsp]
    div r14
    cmp rdx, 0
    jz .fz          # fizzbuzz
    jmp .f         # fizz

# fizzbuzzと表示
.fz:     
    mov rax, 1
    mov rdi, 1
    mov rdx, 9
    lea rsi, [rip+fizzbuzz]
    syscall
    add BYTE PTR [rsp], 1
    jmp .loop
# fizzと表示
.f:
    mov rax, 1
    mov rdi, 1
    mov rdx, 5
    lea rsi, [rip+fizz]
    syscall
    add BYTE PTR [rsp], 1
    jmp .loop
# buzzと表示
.b:
    mov rax, 1
    mov rdi, 1
    mov rdx, 5
    lea rsi, [rip+buzz]
    syscall
    add BYTE PTR [rsp], 1
    jmp .loop
# 数字を表示
.write:
    mov rax, 1
    mov rdx, 1
    mov rdi, 1
    syscall
    ret
#プログラムを終了
.exit:
    mov rax, 60
    syscall
