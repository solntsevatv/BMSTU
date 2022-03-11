PUBLIC GREETS ;глобальная метка процедуры greets
PUBLIC NEW_STR ;глобальная метка процедуры new_str
PUBLIC MAT_MES_PRINT ;глобальная метка процедуры mat_mes_print
PUBLIC OUTMES_PRINT ;глобальная метка процедуры outmes_print

STRDATA SEGMENT PUBLIC PARA 'DATA' ;сегмент данных STRDATA класса 'DATA' с адресом кратным 2
    GRETMES DB 'Enter matrix size: $' ;создаём строку для приглашения ввода с меткой GRETMES
    MATMES DB 'Enter matrix elements:$' ;создаём строку для приглашения ввода элементов матрицы
    OUTMES DB 'Result:$' ;создаём строку для объявления вывода
STRDATA ENDS ;конец сегмента данных STRDATA

OUTCODE SEGMENT PARA PUBLIC 'CODE' ;глобальный сегмент блока кода класса 'CODE' с адресом, кратным 16
SEGSET: ;настройка сегмента и помещение нужной команды в регистр AX
    MOV AX, STRDATA ;перемещаем значение метки STRDATA в AX
    MOV DS, AX ;помещаем значение регистра AX в DS
    MOV AH, 09h ;помещаем в AH команду вывода строки 09h
    RET ;команда возврата из блока кода

NEW_STR PROC FAR ;начало сегмента кода new_str с дальним типом передачи управления
    MOV AH, 02h ;помещаем в AH команду вывода символа на экран 02h
    MOV DL, 13 ;перевод на следующую строку
    INT 21h ;прерывание
    MOV DL, 10 ;возврат каретки
    INT 21h ;прерывание
    RET ;команда возврата из процедуры
NEW_STR ENDP ;конец процедуры

GREETS PROC FAR ;начало процедуры greets с дальним типом передачи управления
    CALL SEGSET
    MOV DX, OFFSET DS:GRETMES ;помещаем в DX строку по метке gretmes
    INT 21h ;выполняем команды с помощью прерывания
    RET ;команда возврата из процедуры
GREETS ENDP ;конец процедуры

MAT_MES_PRINT PROC FAR ;начало процедуры mat_mes_print с дальним типом передачи управления
    CALL SEGSET ;вызываем блок кода, настраивающий регистры
    MOV DX, OFFSET DS:MATMES ;помещаем в DX строку по метке matmes
    INT 21h ;выполняем команды с помощью прерывания
    CALL NEW_STR
    RET ;команда возврата из процедуры
MAT_MES_PRINT ENDP ;конец процедуры

OUTMES_PRINT PROC FAR ;начало процедуры outmes_print с дальним типом передачи управления
    CALL SEGSET ;вызываем блок кода, настраивающий регистры
    MOV DX, OFFSET DS:OUTMES ;помещаем в DX строку по метке outmes
    INT 21h ;выполняем команды с помощью прерывания
    CALL NEW_STR
    RET ;команда возврата из процедуры
OUTMES_PRINT ENDP ;конец процедуры

OUTCODE ENDS ;конец сегмента кода OUTCODE
END ;конец программы