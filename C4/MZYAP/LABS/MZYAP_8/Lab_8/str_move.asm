.686
.model flat, c

public str_move

.stack

.code
str_move proc
    push ebp
    mov ebp, esp

    mov esi, [ebp + 8] ;src
    mov edi, [ebp + 12] ;dst
    mov ecx, [ebp + 16] ;size

    cmp esi, edi

    je equal
    jl lesser
    jg greater

    lesser:
        rep movsb

    greater:
        std
        add ecx, 1
        add esi, ecx
        add edi, ecx
        rep movsb
        cld

    equal:

    pop ebp
    ret
str_move endp
end