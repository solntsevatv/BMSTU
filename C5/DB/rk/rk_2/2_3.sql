/*
Группируем покупателей по их городу, при этом отбрасывая группы в которых только один покупатель.
*/
SELECT city, COUNT(*) AS city_count
FROM buyers
GROUP BY city
HAVING COUNT(*) > 1;