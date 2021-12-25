import tkinter as tk

merge_time = 0
result_str = ""
arr = []

def Read():
  arr = []
  tmp = inputBuffer.get()

  for i in tmp.split(", "):
    arr.append(int(i))

  return arr

def prepare_result(text, arr):

  tmp = text 
  for i in arr:
    tmp += str(i) + " "
  tmp += '\n'
  return tmp

def Merge(front, mid, end):

  global arr
  leftArr = []
  rightArr = [] 
  leftIndex = 0 
  rightIndex = 0 
  originIndex = front
  maxVar = 0 

  for i in range(front, mid+1):
    leftArr.append(arr[i])
    if arr[i] < 0:
      continue
    maxVar += arr[i]

  for i in range(mid+1, end+1):
    rightArr.append(arr[i])
    if arr[i] < 0:
      continue
    maxVar += arr[i]

  leftArr.append(maxVar+1) 
  rightArr.append(maxVar+1)

  while originIndex <= end:
    if leftArr[leftIndex] >= rightArr[rightIndex]:
      arr[originIndex] = rightArr[rightIndex]
      originIndex += 1
      rightIndex += 1
    else:
      arr[originIndex] = leftArr[leftIndex]
      originIndex += 1
      leftIndex += 1

def MergeSort(front, end):

  global arr, result_str, merge_time

  if front < end:
    if (front+end)%2 == 0: 
      midIndex = int((front+end)/2)
    else:
      midIndex = int((front+end-1)/2)

    MergeSort(front, midIndex)
    MergeSort(midIndex+1, end)
    Merge(front, midIndex, end)

  merge_time += 1
  result_str += prepare_result("第" + str(merge_time) + "輪排序結果:", arr)

def MergeSort_handler():
  
  global merge_time, result_str, arr
  result_str = ""
  merge_time = 0

  arr = Read()
  result_str += prepare_result("原始未經排序資料:", arr)
  MergeSort(0, len(arr)-1)
  result_str += prepare_result("最終排序結果:", arr)
  result.set(result_str)

window = tk.Tk()
window.geometry("1400x720")
window.title('sorting')

inputBuffer = tk.StringVar()
result = tk.StringVar()

input1 = tk.Entry(window, textvariable=inputBuffer, font='30')
input1.place(x=500, y=2, width=500, height=30)

button_merge = tk.Button(window, text="MergeSort", font='30', command=MergeSort_handler)
button_merge.place(x=10, y=55)

label_result = tk.Label(window, textvariable=result, font='30', justify='left') 
label_result.place(x=300, y=100)

tk.mainloop()
