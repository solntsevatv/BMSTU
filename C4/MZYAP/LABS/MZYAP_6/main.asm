EXTRN STRGET: FAR
EXTRN PRINT8C: FAR
EXTRN PRINT16C: FAR
PUBLIC NUM

STACKSEG SEGMENT STACK PARA 'STACK'
    DB 100 DUP(0)
STACKSEG ENDS

DATA SEGMENT PUBLIC PARA 'DATA'
    NUM DW 1 DUP(0)
    OPTIONS DD EXIT, PRINT8C, PRINT16C, STRGET
    MENU DB 13, 10, "Options:", 13, 10
    DB " 0. Exit", 13, 10
    DB " 1. Out in oct unsigned", 13, 10
    DB " 2. Out in hex signed", 13, 10
    DB " 3. In binary signed", 13, 10
    DB "> $"

DATA ENDS

CODESEG SEGMENT PARA 'CODE'
EXIT:
    MOV AX, 4C00h
    INT 21h
MAIN:
    MOV AX, DATA
    MOV DS, AX
    
    MAINMENU:
        MOV AH, 09h
        MOV DX, OFFSET MENU
        INT 21h

        MOV AH, 01h
        INT 21h
        SUB AL, '0'
        XOR DI, DI
        XCHG DI, BX
        MOV BX, 4
        MUL BL
        MOV BL, AL
        XCHG BX, DI

        MOV AH, 02h
        MOV DL, 13
        INT 21h
        MOV DL, 10
        INT 21h 

        MOV AX, DATA
        MOV ES, AX
        PUSH DS
        CALL DS:OPTIONS[DI]
        POP DS

        JMP MAINMENU
CODESEG ENDS
END MAIN