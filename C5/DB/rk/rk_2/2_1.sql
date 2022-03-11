/*
Данный запрос работает с таблицей букетов. Его смысл заключается в том, что он проверяет id автора,
и в зависимости от его значения относит букет к одной из трёх групп.
*/
SELECT id, title,
CASE 
WHEN author < 3 THEN 'group one'
WHEN author >= 3 AND author < 6 THEN 'group two'
WHEN author >=6 THEN 'group three'
END
FROM bouquets;