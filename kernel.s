BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax ;セグメントレジスタ初期化
    mov ds, ax
    mov es, ax
    mov ss, ax

.print:
    mov ah, 0x00
    int 0x16 ;ディスクサービス
    
    mov ah, 0x0e
    mov bh, 0x0
    mov bl, 0
    int 0x10 ;ビデオサービス
    cmp al, 0x41
    jz .reboot
    jmp .print

.reboot:
    int 0x19 ;再起動

times 510 - ($ - $$) db 0
dw 0xAA55

