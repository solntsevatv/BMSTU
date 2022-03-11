import random as rd

def generate_random_test_array(len):
  arr = []
  for i in range(0, len):
    arr.append(rd.randint(-100, 100))
  return arr

def bubble_sort(arr):
  size = len(arr) - 1
  swap = True
  while swap:
    swap = False
    for i in range(0, size):
      if arr[i] > arr[i + 1]:
        buff = arr[i]
        arr[i] = arr[i + 1]
        arr[i + 1] = buff
        swap = True
    size -= 1
  return arr

def comb_sort(arr):
  size = len(arr) - 1
  k = 1
  step = size - 1
  while step > 1:
    diff = len(arr) - int(step)
    for i in range(0, diff):
      if arr[i] > arr[i + int(step)]:
        buff = arr[i]
        arr[i] = arr[i + 1]
        arr[i + 1] = buff
    step -= k
  swap = True
  while swap:
    swap = False
    for i in range(0, size):
      if arr[i] > arr[i + 1]:
        buff = arr[i]
        arr[i] = arr[i + 1]
        arr[i + 1] = buff
        swap = True
    size -= 1
  return arr 

def insert_sort(arr):
  for i in range(1, len(arr)):
    temp = arr[i]
    j = i - 1
    while (j >= 0 and temp < arr[j]):
        arr[j + 1] = arr[j]
        j -= 1
    arr[j + 1] = temp
  return arr