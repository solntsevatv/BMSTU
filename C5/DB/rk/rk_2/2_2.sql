/*
Заменяет название букета на имя его автора.
*/
UPDATE bouquets
SET title = (SELECT fio FROM florists WHERE id = author);