import random as rd

def generate_stair_records(n):
    record = ''
    for i in range(0, n):
        record += '(' + str(i + 1) + ', '
        record += str(rd.randint(1, 25)) + ', '
        record += str(rd.randint(1, 2000)) + ', '
        record += str(rd.randint(15, 19)) + ', '
        record += str(rd.randint(105, 215)) + ', '
        record += str(rd.randint(25, 35))
        record += '),\n'
    return record

#print(generate_stair_records(10))