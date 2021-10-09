section .text
    extern ISR_ExceptionHandler
    global __ISR_Exception_00
    global __ISR_Exception_01
    global __ISR_Exception_02
    global __ISR_Exception_03
    global __ISR_Exception_04
    global __ISR_Exception_05
    global __ISR_Exception_06
    global __ISR_Exception_07
    global __ISR_Exception_08
    global __ISR_Exception_09
    global __ISR_Exception_10
    global __ISR_Exception_11
    global __ISR_Exception_12
    global __ISR_Exception_13
    global __ISR_Exception_14
    global __ISR_Exception_15
    global __ISR_Exception_16
    global __ISR_Exception_17
    global __ISR_Exception_18
    global __ISR_Exception_19
    global __ISR_Exception_20
    global __ISR_Exception_21
    global __ISR_Exception_22
    global __ISR_Exception_23
    global __ISR_Exception_24
    global __ISR_Exception_25
    global __ISR_Exception_26
    global __ISR_Exception_27
    global __ISR_Exception_28
    global __ISR_Exception_29
    global __ISR_Exception_30
    global __ISR_Exception_31
    global __ISR_Exception_128

__ExceptionHandler:
    pusha                       ; push all registers
    mov ax, ds
    push eax                    ; save ds

    mov ax, 0x10                ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call ISR_ExceptionHandler

    pop ebx                     ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 0x8
    sti
    iret

__ISR_Exception_00:
    cli
    push byte 0
    push 0
    jmp __ExceptionHandler

__ISR_Exception_01:
    cli
    push byte 0
    push 1
    jmp __ExceptionHandler

__ISR_Exception_02:
    cli
    push byte 0
    push 2
    jmp __ExceptionHandler

__ISR_Exception_03:
    cli
    push byte 0
    push 3
    jmp __ExceptionHandler

__ISR_Exception_04:
    cli
    push byte 0
    push 4
    jmp __ExceptionHandler

__ISR_Exception_05:
    cli
    push byte 0
    push 5
    jmp __ExceptionHandler

__ISR_Exception_06:
    cli
    push byte 0
    push 6
    jmp __ExceptionHandler

__ISR_Exception_07:
    cli
    push byte 0
    push 7
    jmp __ExceptionHandler

__ISR_Exception_08:
    cli
    push byte 0
    push 8
    jmp __ExceptionHandler

__ISR_Exception_09:
    cli
    push byte 0
    push 9
    jmp __ExceptionHandler

__ISR_Exception_10:
    cli
    push 10
    jmp __ExceptionHandler

__ISR_Exception_11:
    cli
    push 11
    jmp __ExceptionHandler

__ISR_Exception_12:
    cli
    push 12
    jmp __ExceptionHandler

__ISR_Exception_13:
    cli
    push 13
    jmp __ExceptionHandler

__ISR_Exception_14:
    cli
    push 14
    jmp __ExceptionHandler

__ISR_Exception_15:
    cli
    push byte 0
    push 15
    jmp __ExceptionHandler

__ISR_Exception_16:
    cli
    push byte 0
    push 16
    jmp __ExceptionHandler

__ISR_Exception_17:
    cli
    push byte 0
    push 17
    jmp __ExceptionHandler

__ISR_Exception_18:
    cli
    push byte 0
    push 18
    jmp __ExceptionHandler

__ISR_Exception_19:
    cli
    push byte 0
    push 19
    jmp __ExceptionHandler

__ISR_Exception_20:
    cli
    push byte 0
    push 20
    jmp __ExceptionHandler

__ISR_Exception_21:
    cli
    push byte 0
    push 21
    jmp __ExceptionHandler

__ISR_Exception_22:
    cli
    push byte 0
    push 22
    jmp __ExceptionHandler

__ISR_Exception_23:
    cli
    push byte 0
    push 23
    jmp __ExceptionHandler

__ISR_Exception_24:
    cli
    push byte 0
    push 24
    jmp __ExceptionHandler

__ISR_Exception_25:
    cli
    push byte 0
    push 25
    jmp __ExceptionHandler

__ISR_Exception_26:
    cli
    push byte 0
    push 26
    jmp __ExceptionHandler

__ISR_Exception_27:
    cli
    push byte 0
    push 27
    jmp __ExceptionHandler

__ISR_Exception_28:
    cli
    push byte 0
    push 28
    jmp __ExceptionHandler

__ISR_Exception_29:
    cli
    push byte 0
    push 29
    jmp __ExceptionHandler

__ISR_Exception_30:
    cli
    push byte 0
    push 30
    jmp __ExceptionHandler

__ISR_Exception_31:
    cli
    push byte 0
    push 31
    jmp __ExceptionHandler

__ISR_Exception_128:
    cli
    push byte 0
    push 128
    jmp __ExceptionHandler