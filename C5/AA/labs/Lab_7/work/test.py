from algos import *

t_records = {"Петровский Федосей Тарасович" : "Борисов Фока Павлович",
"Нестеров Сила Вячеславович" : "Иванов Пантелеймон Семёнович",
"Лебедева Октябрина Михайловна" : "Майоров Никодим Арсеньевич",
"Титова Злата Борисовна" : "Бычкова Вероника Борисовна",
"Малышева Марина Максимовна" : "Никонова Милица Андреевна",
"Добрынина Елена Олеговна" : "Кукушкина Матрёна Владимировна",
"Савицкий Севастьян Макарович" : "Еремеев Виталий Маркович",
"Панкова Инна Марковна" : "Гришина Карина Каллиниковна",
"Русаков Тарас Федотович" : "Жилин Савва Владиславович"}

# Key at beginning
t_1_key = "Петровский Федосей Тарасович"
t_1_correct = "Борисов Фока Павлович"
# Key at the end
t_2_key = "Малышева Марина Максимовна"
t_2_correct = "Никонова Милица Андреевна"
# Key at center
t_3_key = "Русаков Тарас Федотович"
t_3_correct = "Жилин Савва Владиславович"
# Key not from dictionary
t_4_key = "aboba"
t_4_correct = -1

keys = [t_1_key, t_2_key, t_3_key, t_4_key]
correct = [t_1_correct, t_2_correct, t_3_correct, t_4_correct]

print("Tests for sequence search:")
for i in range(0, 4):
    result = seq_search(t_records, keys[i])
    if result == correct[i]:
        print("PASSED")
    else:
        print("FAILED")

print("Tests for binary search:")
for i in range(0, 4):
    result = bin_search(t_records, keys[i])
    if result == correct[i]:
        print("PASSED")
    else:
        print("FAILED")

print("Tests for segment search:")
for i in range(0, 4):
    result = seg_search(gen_dict_for_seg(t_records), keys[i])
    if result == correct[i]:
        print("PASSED")
    else:
        print("FAILED")