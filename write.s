.intel_syntax noprefix
.global _start
_start:
  push rbp
  mov rbp, rsp                  # スタックの確保
  sub rsp, 0x8                　# ８バイト確保
  mov DWORD PTR [rbp], 0x41     # 文字列”A"
  mov rax, 1                    # write()
  mov rdx, 1                    # 文字数1
  mov rdi, 1                    # 出力
  lea rsi, [rbp]                # 文字のアドレス
  syscall                       # 画面に出力

  mov rax, 60                   # exit() 
  syscall                       # プログラムを終了
