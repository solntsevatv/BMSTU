a = str(input())
symb_list = []
in_flag = False
for i in range(0, len(a)):
    in_flag = False
    for j in range(0, len(symb_list)):
        if a[i] == symb_list[j]:
            in_flag = True
    if in_flag != True:
        symb_list.append(a[i])
C_n_m = 0
n = len(symb_list)
m = len(a)
C_numerator = 1
for i in range(1, m + n):
    C_numerator = C_numerator * i
C_denominator_m = 1
for i in range(1, m):
    C_denominator_m = C_denominator_m * i
C_denominator_n = 1
for i in range(1, n + 1):
    C_denominator_n = C_denominator_n * i
C_n_m = C_n_m + int(C_numerator / (C_denominator_n * C_denominator_m))
print(C_n_m)