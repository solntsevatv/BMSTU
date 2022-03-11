PUBLIC ELEMS
PUBLIC MATRIX

PUBLIC READ_SYMB
PUBLIC READ_MAT
PUBLIC PRINT_MAT
PUBLIC ELEM_COL

EXTRN NEW_STR: FAR

MATDATA SEGMENT PUBLIC PARA 'DATA' ;сегмент данных для матрицы
    MATRIX DB 82 DUP('$') ;создание строки и запись в неё символа конца строки
    ELEMS DB 1 DUP(0) ;количество элементов в строке
    ELEM_COL DB 1 DUP(0) ;количество элементов в матрице
MATDATA ENDS

READCODE SEGMENT PARA PUBLIC 'CODE' 
SEGSET: ;настройка сегмента и помещение нужной команды в регистр AX
    MOV AX, MATDATA ;перемещаем значение метки MATRIX в AX
    MOV DS, AX ;помещаем значение регистра AX в DS
    RET ;команда возврата из блока кода

READ_SYMB PROC FAR ;процедура считывания символа в регистр BH
    MOV AH, 08h
    INT 21h
    MOV BH, AL
    MOV DL, AL
    MOV AH, 02h
    INT 21h
    MOV DL, ' '
    INT 21h
    RET
READ_SYMB ENDP

READ_MAT PROC FAR
    CALL SEGSET
    SUB BH, 48
    MOV DS:ELEMS, BH

    MOV AL, DS:ELEMS
    MUL DS:ELEMS

    MOV DS:ELEM_COL, AL

    MOV CX, AX
    MOV DH, 0h
    READ_ONE_NUM:
        CALL READ_SYMB
        
        MOV AX, BX
        MOV BX, 0
        MOV BL, DH

        MOV DS:MATRIX[BX], AH
        INC DH

        MOV AH, 00h
        MOV AL, DH
        MOV BH, DS:ELEMS
        DIV BH
        CMP AH, 00h
        JNE CONTINUE
        CALL NEW_STR
        CONTINUE:
        LOOP READ_ONE_NUM
    RET
READ_MAT ENDP

PRINT_MAT PROC FAR
    CALL SEGSET
    MOV AL, DS:ELEMS
    MUL DS:ELEMS

    MOV CX, AX
    MOV DH, 0h
    PRINT_ONE_NUM:
        MOV AX, BX
        MOV BX, 0
        MOV BL, DH

        MOV DL, DS:MATRIX[BX]
        MOV AH, 02h
        INT 21h
        MOV DL, ' '
        INT 21h

        INC DH

        MOV AH, 00h
        MOV AL, DH
        MOV BH, DS:ELEMS
        DIV BH
        CMP AH, 00h
        JNE CONTINUE
        CALL NEW_STR
        CONTINUE:
        LOOP PRINT_ONE_NUM
    RET
PRINT_MAT ENDP

READCODE ENDS
END