def bubble_sort(arr):
  size = len(arr) - 1 # 2
  swap = True # 1
  while swap: # 1
    swap = False # 1
    for i in range(0, size): # 3
      if arr[i] > arr[i + 1]: # 4
        buff = arr[i] # 2
        arr[i] = arr[i + 1] # 4
        arr[i + 1] = buff # 3
        swap = True # 1
    size -= 1 # 1
  return arr

def comb_sort(arr):
  size = len(arr) - 1 # 2
  k = 1 # 1
  step = size - 1 # 2
  while step > 1: # 1
    diff = len(arr) - step # 2
    for i in range(0, diff): # 3
      if arr[i] > arr[i + step]: # 1 + 1 + 2
        buff = arr[i] # 2
        arr[i] = arr[i + 1] # 4
        arr[i + 1] = buff # 3
    step -= k # 1
  swap = True # 1
  while swap: # 1
    swap = False # 1
    for i in range(0, size): # 3
      if arr[i] > arr[i + 1]: # 4
        buff = arr[i] # 2
        arr[i] = arr[i + 1] # 4
        arr[i + 1] = buff # 4
        swap = True # 1
    size -= 1 # 1
  return arr 

def insert_sort(arr):
  for i in range(0, len(arr)): # 3
    j = i # 1
    while j > 0 and arr[j - 1] > arr[j]: # 1 + 1 + 2 + 1 + 1
      buff = arr[i] # 2
      arr[i] = arr[i + 1] # 1 + 1 + 2
      arr[i + 1] = buff # 2 + 1
      j -= 1 # 1
  return arr