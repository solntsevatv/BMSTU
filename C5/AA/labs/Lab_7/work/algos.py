def seq_search(data, key):
    for elem in data:
        if key == elem:
            return data[elem]
    return -1

def bin_search(data, key):
    list_keys = sorted(list(data.keys()))
    l, r = 0, len(list_keys) - 1
    while l <= r:
        middle = (l + (r - l) // 2)

        if list_keys[middle] == key:
            return data[key]
        elif list_keys[middle] < key:
            l = middle + 1
        else:
            r = middle - 1

    return -1

def bin_search_presort(data, key, list_keys):
    l, r = 0, len(list_keys) - 1
    while l <= r:
        middle = (l + (r - l) // 2)
        
        if list_keys[middle] == key:
            return data[key]
        elif list_keys[middle] < key:
            l = middle + 1
        else:
            r = middle - 1
    return -1

def sort_by_vals(sort_dict):
    new_dict = dict()

    list_d = list(sort_dict.items())
    list_d.sort(key=lambda i: i[1], reverse=True)
    for x in list_d:
        new_dict[x[0]] = x[1]

    return new_dict

def gen_dict_for_seg(data):
    dcount = {i : 0 for i in "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"}

    for key in data:
        dcount[key[0]] += 1
    
    dcount = sort_by_vals(dcount)
    new_dict = {i : dict() for i in dcount}
    for key in data:
        new_dict[key[0]].update({key: data[key]})
    return new_dict

def seg_search(data, key):
    for k in data:
        if key[0] == k:
            for elem in data[k]:
                if elem == key:
                    return data[k][elem]
    return -1

if __name__ == '__main__':
    t_records = {"Петровский Федосей Тарасович" : "Борисов Фока Павлович",
    "Нестеров Сила Вячеславович" : "Иванов Пантелеймон Семёнович",
    "Лебедева Октябрина Михайловна" : "Майоров Никодим Арсеньевич",
    "Титова Злата Борисовна" : "Бычкова Вероника Борисовна",
    "Малышева Марина Максимовна" : "Никонова Милица Андреевна",
    "Добрынина Елена Олеговна" : "Кукушкина Матрёна Владимировна",
    "Савицкий Севастьян Макарович" : "Еремеев Виталий Маркович",
    "Панкова Инна Марковна" : "Гришина Карина Каллиниковна",
    "Русаков Тарас Федотович" : "Жилин Савва Владиславович"}

    print(list(t_records))

    #print(seg_search(gen_dict_for_seg(t_records), 'Добрынина Елена Олеговна'))