# Базы данных. Семинар 6. 13.10.2021
## Функции, процедуры, триггеры и курсоры на примере языка transactSQL.
Функции разлечаются по поведению
* Детерминированная - при одном и том же заданном входном значении она всегда возвращает один и тот же результат.
* Недетерминированная - возвращает различные значения при одном и том же заданном входном значении.

Все пользовательские функции - недетерминированные.

Функции по типу возвращаемого значения:
* Скалярная функция
* Подставляемая табличная функция
* Многооператорная табличная функция

### Скалярная функия
Возвращает некое скалярное значение. Обычно используется в функции select

Синтаксис:\
CREATE FUNCTION [ИМЯ-СХЕМЫ] ИМЯ-ФУНКЦИИ ([СПИСОК-ОБЪЯВЛЕНИЙ-ПАРАМЕТРОВ])\
RETURNS СКАЛЯРНЫЙ-ТИП-ДАННЫХ\
[WITH СПИСОК-ОПЦИЙ-ФУНКЦИЙ]\
[AS]\
BEGIN\
ТЕЛО-ФУНКЦИИ\
RETURN СКАЛЯРНОЕ-ВЫРАЖЕНИЕ\
END[;]

Пример:\
CREATE FUNCTION dbo.AveragePrice() RETURNS smallmoney\
WITH SCHEMABIDING AS\
BEGIN\
RETURN (SELECT AVG(Price) FROM dbo.R)\
END;

CREATE FUNCTION dbo.PriceDifference(@Price smallmoney)\
RETURNS smallmoney AS\
BEGIN\
RETURN @Price - dbo.AveragePrice()\
END;

Вызов функции
SELECT Pname, Price, dbo.AveragePrice() AS Average,\
dbo.PriceDifference(Price) AS Difference\
FROM R\
WHERE City='Смоленск'\

### Подставляемая табличная функция
Синтаксис:\
CREATE FUNCTION [ИМЯ-СХЕМЫ] ИМЯ-ФУНКЦИИ ([СПИСОК-ОБЪЯВЛЯЕМЫХ ПАРАМЕТРОВ])\
RETURNS TABLE\
[WITH СПИСОК-ОПЦИЙ-ФУНКИЙ]\
[AS]\
RETURN [(] ВЫРАЖЕНИЕ-ВЫБОРКИ [)]\
END [;]

Пример:\
CREATE FUNCTION dbo.FullSPJ()\
RETURNS TABLE\
AS\
RETURN (\
SELECT S.Sname, P.Pname, J.Jname, SPJ.Qty\
FROM S INNER JOIN SPJ ON S.Sno = SPJ.Sno\
INNER JOIN P ON P.Pno = SPJ.Pno\
INNER JOIN J ON J.Jno = SPJ.Jno)

Вызов функции:\
SELECT *\
FROM dbo.FullSPJ()

### Многооператорная функция

Синтаксис:\
CREATE FUNCTION [ИМЯ-СХЕМЫ] ИМЯ-ФУНКЦИИ ([СПИСОК-ОБЪЯВЛЕНИЙ-ПАРАМЕТРОВ])\
RETURNS @ИМЯ-ВОЗВРАЩАЕМОЙ-ПЕРЕМЕННОЙ\
TABLE ОПРЕДЕЛЕНИЕ-ТАБЛИЦЫ\
[WITH СПИСОК-ОПЦИЙ-ФУНКЦИЙ]\
[AS]\
BEGIN\
RETURN END [;]

Пример:
CREATE FUNCTION dbo.fnGetReports (@EmployeeID AS int)\
RETURNS @Reports TABLE (EmplyeeID int NOT NULL, ReportsToID int NULL)\
AS [у постреса отдельный блок с объявлением всех переменных] BEGIN\
DECLARE @Employee AS int\
INSERT INTO @Reports\
SELECT EmployeeID, ReportsTo FROM EmplOyees\
WHERE EmployeeID = @EmployeeID\
SELECT @Employee = MIN(EmployeeID) FROM Employees\
WHERE ReportsTo = @EmployeeID\
WHILE @Employee IS NOT NULL\
BEGIN\
INSERT INTO @Repotrs\
SELECT * FROM Employees\
END\
RETURN

В третьей лабораторной должно быть много операторов внутри тела функции.

### Хранимая процедура
Некий объект базы данных, представляющий из себя набор инструкции. Компилируется один раз, хранится на сервере.

Синтаксис:\
CREATE PROCEDURE [ИМЯ-СХЕМЫ] ИМЯ-ПРОЦЕДУРЫ [СПИСОК-ОБЪЯВЛЕНИЙ-ПАРАМЕТРОВ]\
[WITH СПИСОК-ОПЦИЙ-ПРОЦЕДУРЫ]\
[FOR REPLICATION]\
AS\
ТЕЛО-ПРОЦЕДУРЫ\
[;]

Пример:\
CREATE PROCEDURE dbo.Factorial @ValIn bigint, @ValOut bigint outpub\
AS\
BEGIN\
IF @ValIn > 20 BEGIN\
PRINT N'Входной параметр не должен быть <= 20' -- вывод ошибки\
RETURN 99 -- код ошибки\
END\
DECLARE @WorkValIn bigint, @WorkValOur bigint\
IF @ValIn != 1\
BEGIN\
SET @WorkValIn = @ValIn - 1\
PRINT @@NESTLEVEL\
EXEC dbo.Factorial @WorkValIn, @WorkValOut OUTPUT\
SET @ValOut = @WorkValOut * @ValIn\
END\
ELSE\
SET @ValOut = 1

В постгрес собака не используется, есть local и global, local - по умолчанию, global - нужно указывать.

Процедуры могут быть вложенны, максимальный уровень - 32.

NESTLEVEL - уровень глубины вложенности процедуры (текущий)

Для вызова процедуры используется ключевое слово EXEC, после которого идёт имя вызываемой процедуры и параметры. Также через EXEC можно вызвать функцию.

Вызов хранимой процедуры:\
DECLARE @FactIn int, @FacOut int\
SET @FactIn = 8\
EXEC dbo.Factorial, @FactIn, @FactOut OUTPUT\

PRINT N'Факториал ' + CONVERT(varchar(3), @FactIn) + N'РАВЕН ' + CAST(@FactOut AS varchar(20))

## Триггеры

Триггер - хранимая процедура особого типа, которая выполняет одну или несколько инструкций в ответ на событие.

По типу события триггеры делятся на два класса:
* DDL-триггеры
* DML-триггеры

События делятся на события на уровне базы данных и на события на уровне сервера. 

DDL-триггеры.

Триггер DDL может активироваться, если выполняется такая инструкция, как ALTER SERVER CONFIGURATION, или если происходит удаление таблицы с использованием команды DROP TABLE.

Пример триггера:\
CREATE TRIGGER SAFETY\
ON DATABASE\
FOR DROP_TABLE, ALTER_TABLE - события, на которые триггер срабатывает\
AS\
    PRINT 'You must disable Trigge "safety" to drop or alter tables'\
    ROLLBACK; - откат действия\

DML-триггеры

Для поддержания согласованности и точности данных используются декларативные и процедурные методы.

Триггеры применяются в следующих случаях:\
* если использование методов декларативной целостности данных не отвечает функциональным потребностям приложения
* если необходимо каскадное изменение через связанные таблицы в базе данных
* если база данных денормализована и требуется способ автоматизированного обновления избыточных данных в нескольких таблицах
* если необходимо сверить значение в одной таблице с неидентичным значением в другой таблице
* если требуеся вывод пользовательских сообщений и сложная обработка ошибек

Классы DML-триггеров
- INSTEAD OF - триггер выполняется в обход действий, вызывавших их срабатывание, заменяя эти действия. Например, обновление таблицы, в которой есть триггер INSTEAD OF, вызовет срабатывание этого триггера. В результате вместо оператора обновления выполняется код триггера.
- AFTER/BEFORE - триггеры этого класса исполняются после или до действия, вызвавшего выполения триггера.

Синтаксис:\
CREATE TRIGGER имя_триггера\
ON имя_таблицы_или_представления\
[WITH ENCRYPTION]\
класс_триггера тип(ы)_триггера\
[WITH APPEND]\
[NOT FOR DECLARATION]\
AS sql_инструкции\

Пример:\
CREATE TRIGGER AfterUpdateSPJ\
ON dbo.SPJ\
AFTER UPDATE\
AS\
BEGIN\
RAISERROR(N'Произошло обновление в таблице поставок',1,1)\
END

