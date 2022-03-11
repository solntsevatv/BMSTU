# PROCESS FLAGS
The sum of these values is displayed in the "F" column, which is provided by the flags output specifier:
* 0 - normal execution
* 1 - forked but didn't exec
* 4 - used super-user privileges

Process state codes:\
...

Коды выполнения fork коррелируют с COW, связано с разделение адресного пространства предка и потомка.

R - running or runnable - система не различает процессы, которые готовы к выполнению и выполняются.

8 - sleep (блокировка)

WCHAN - на чём блокирован процесс.

PROCESS STATE CODES
Here are the different values that the s, stat and state output specifiers (header "STAT" or "S") will display to describe the state of a process:
    D    uninterruptible sleep (usually IO)
    I    Idle kernel thread
    R    running or runnable (on run queue)
    S    interruptible sleep (waiting for an event to complete)
    T    stopped by job control signal
    t    stopped by debugger during the tracing
    W    paging (not valid since the 2.6.xx kernel)
    X    dead (should never be seen)
    Z    defunct ("zombie") process, terminated but not reaped by its parent

For BSD formats and when the stat keyword is used, additional characters may be displayed:
    <    high-priority (not nice to other users)
    N    low-priority (nice to other users)
    L    has pages locked into memory (for real-time and custom IO)
    s    is a session leader
    l    is multi-threaded (using CLONE_THREAD, like NPTL pthreads do)
    +    is in the foreground process group

Суперюзер это пользователь, который имеет доступ к структурам и командам ядра.

ls -al

Unix различает 7 типов файла:\
\- обычный файл - хранятся на на устройствах как долгосрочный хранитель информации\
d - директория\ 
l - символическая ссылка\
p - именованный программный канал\
s - сокет\
c - специальный файл символьного устройства\
b - специальный файл блочного устройства\

Система различает два типа устройств - символьные и блочные.\
В UNIX всё файл.\

Права доступа:\
1 - юзер\
2 - группа\
3 - остальные\

Столбик чисел - хардлинки, UNIX поддерживает два типа линков - softlink и hardlind\
hardlink - ещё одно равноправное имя файла. В UNIX имя файла не является его идентификатором, идентификатором файла является inode. Для получения номера inode нужно использовать команду ls -lai. inode - структура, в ls -lai - номер inode.\

Полное имя - путь файла + короткое имя. В текущей директории можно использовать короткие имена файлов.

softlink - специальный файл, содержащий путь к файлу - символьную строку.