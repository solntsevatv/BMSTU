from threading import *
import threading
from time import *
from random import *

'''
def test_func(thread_num: int, num: int):
    sleep(randint(0, 5))
    num = thread_num
    print(thread_num)

test_threads = []

for i in range(0, 5):
    thread = Thread(target=test_func, args=(i, i))
    thread.start()
    test_threads.append(thread)

for thread in test_threads:
    thread.join()
'''

'''
curr_conns = {1, 2, 3, 4}
visited = {2, 5, 6, 1, 8}
diff = curr_conns - (visited & curr_conns)
print(diff)
'''
'''
main_list = [[None]] * 5

print(main_list)

def test(test_list, index):
    test_list[index] = [1]

for i in range(0, 5):
    test(main_list, i)

print(main_list)
'''

res = [1, 2, 3]
p = 4
res_ = [p]
res_.extend(res)
print(res_)