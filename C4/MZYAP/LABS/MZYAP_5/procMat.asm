EXTRN MATRIX: BYTE
EXTRN ELEMS: BYTE
EXTRN ELEM_COL: BYTE

PUBLIC PROCESS_MAT

STACKSEG SEGMENT PARA STACK 'STACK' ;сегмент стека класса STACK по адресу кратному 16
    DB 100h DUP (0) ;выделяем стек размером 100 байт
STACKSEG ENDS ;конец сегмента стека

PROCDATA SEGMENT PARA 'DATA' ;сегмент данных для локальных переменных
    MAX_SYMB DB 1 DUP('$') ;символ с максимальным количеством вхождений
    MAX_ENT DB 1 DUP(0) ;память для максимального количества вхождений символа
PROCDATA ENDS

PROCCODE SEGMENT PUBLIC PARA 'CODE'
ES_SEGSET: ;настройка сегмента и помещение нужной команды в регистр AX
    MOV AX, PROCDATA ;перемещаем значение метки MATRIX в AX
    MOV ES, AX ;помещаем значение регистра AX в DS
    RET ;команда возврата из блока кода

COUNT_ENTRIES PROC NEAR
    MOV AH, 00h
    MOV AL, DS:ELEM_COL
    MOV CX, AX
    MOV AL, DH
    MOV DL, 00h
    MOV DH, 00h
    SEARCH:
        MOV BX, 00h
        MOV BL, DL
        MOV AH, DS:MATRIX[BX]

        INC DL
        
        MOV BX, 00h
        MOV BL, AL
        MOV BH, DS:MATRIX[BX]
        CMP AH, BH

        JNE CONTINUE
        INC DH
        CONTINUE:
        LOOP SEARCH
    RET
COUNT_ENTRIES ENDP

SEARCH_SYMB PROC NEAR
    PUSH DX
    CALL COUNT_ENTRIES
    MOV BX, DX
    POP DX
    MOV DL, BH ;количество вхождений элемента с индексом из DH

    CMP DL, ES:MAX_ENT
    JL CONTINUE
    MOV BX, 00h
    MOV BL, DH
    MOV AL, DS:MATRIX[BX]
    MOV ES:MAX_SYMB, AL
    MOV ES:MAX_ENT, DL
    CONTINUE:
    
    INC DH
    CMP DH, DS:ELEM_COL
    JNE SEARCH_SYMB 
    RET
SEARCH_SYMB ENDP

CHANGE_SYMB PROC NEAR
    MOV AX, 00h
    MOV AL, ES:MAX_ENT
    MOV BL, 09h
    DIV BL
    ADD AH, '0' ;остаток

    MOV CH, 00h
    MOV CL, DS:ELEM_COL

    MOV BX, 00h ;индекс
    MOV DL, ES:MAX_SYMB

    CHANGE:
        CMP DL, DS:MATRIX[BX]
        JNE CONTINUE
        MOV DS:MATRIX[BX], AH
        CONTINUE:
        INC BX
        LOOP CHANGE
    RET
CHANGE_SYMB ENDP

PROCESS_MAT PROC FAR
    CALL ES_SEGSET

    MOV DH, 00h
    MOV BX, 0
    MOV BL, DH
    MOV DL, DS:MATRIX[BX]
    MOV ES:MAX_SYMB, DL
    MOV ES:MAX_ENT, 01h

    CALL SEARCH_SYMB
    CALL CHANGE_SYMB
    RET
PROCESS_MAT ENDP

PROCCODE ENDS
END