STACKSEG SEGMENT STACK PARA 'STACK'
    DB 100h DUP(0)
STACKSEG ENDS

CODESEG SEGMENT PARA 'CODE'

MAIN:
    MOV SI, 10h
    MOV DI, 10h
    MOV DX, 1234h
CODESEG ENDS
END MAIN