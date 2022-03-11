f = open('departaments.txt', 'r', encoding='utf8')
f_n = open('new_departaments.txt', 'w', encoding='utf8')

line_num = 1

for line in f:
    try:
        int(line[len(line) - 2])
        f_n.write(line)
    except:
        pass