__Print:
    pusha

__start:
    mov al, [bx]
    cmp al, 0 
    je __end

    ; Print using BIOS interrupt
    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp __start

__end:
    popa
    ret

__PrintNL:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

__PrintHex:
    pusha
    mov cx, 0

__loop:
    cmp cx, 4
    je __end
    
    mov ax, dx
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39
    jle __step2
    add al, 7

__step2:
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    add cx, 1
    jmp __loop

__end:
    mov bx, HEX_OUT
    call __Print

    popa
    ret

HEX_OUT:
    db '0x0000',0