Лаба 2:
PPID = 1, так как когда мы завершаем родительский процесс, процесс-демон усыновляется процессом init, PID которого равен 1. Процесс init - системный демон, отвечающий за запуск различных системных служб на разных уровнях загрузки.
PID = 1651 идентификатор процесса, доставшийся "в наследство" от процесса, породившего демона
PGID = id группа процессов, лидером которой является процесс-демон
SID = id сессии, равно PGID, так как процесс является лидером сессии
TTY = ?, так как процесс-демон не имеет управляющего терминала
TPGID = id группы процессов, контролирующей терминалы, -1, так как нет управляющего терминала
STAT - коды статуса процесса, S - прерываемый сон, s - лидер сессии, l - многопоточный
UID - текущий пользователь

Лаба 3 - В функцию exit модуля надо включить printk(current) для вывода информации о текущем процессе.

Какие функции ядра вы использовали в этом модуле?
printk - вывод в системный журнал
module_init - макрос
module_exit - макрос

Функция next_task - переход к следующему task

Когда вызывается init и exit - при вызове команд insmod и rmmod

Для чего вы написали модуль ядра?
Для того, чтобы получить доступ к струткуре ядра struct task_struct.
Структура task_struck, являющаяся дескриптором процесса.

Какие фукнции вы реализовали, где они находятся, что они делают?
функции инициализации и выхода из модуля

Имеет ли значение порядок загрузки модулей - имеет, модуль может быть корректно загружен только если загружены все его зависимости

v В модуле 2 вызвать локальную функцию, получить ошибку, проанализировать
v Вызов no export как у Цирюльника
v Прописать no_export в header как extern и вызвать в модуле 2, получить ошибку, анализировать на каком этапе
v Вызвать функции в модуле 3, комментировать ошибку
v Оставить правильные вызовы и попытаться сначала загрузить второй модуль, потом первый

Лаба 4 - первая часть task/prod/pid/maps(pagemap)/comm/IO/root - вывод