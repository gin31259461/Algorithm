import tkinter as tk

ovals = []
ovalText = []
lines = []

window = tk.Tk()

def Read():
    
  readline = []
  preorder = []
  inorder = []

  tmp = input1.get(1.0, "end-1c")

  for i in tmp.split("\n"):
    readline.append(i)

  for i in readline[0].split(", "):
    preorder.append(i)

  for i in readline[1].split(", "):
    inorder.append(i)

  return preorder, inorder

class node():
  
  def __init__(self, x0, y0, x1, y1):
    self.p1 = [x0, y0]
    self.p2 = [x1, y1]
    self.xy = [x0, y0, x1, y1]

def binary_tree_traversal(ordermember):

  global ovals, ovalText, lines
   
  nodes = [] 
  width = 25
  moveX = 200
  moveY = 100

  cv = tk.Canvas(window, bg='white', height=700, width=1000)
  cv.place(x=200, y=100)

  #root
  nodes.append(node(500, 50, 550, 100))
  ovals.append(cv.create_oval(nodes[0].xy, fill='lightgrey'))
  ovalText.append(cv.create_text(nodes[0].p1[0] + width, nodes[0].p1[1] + width, text=ordermember[0], font='30'))

  #1
  nodes.append(node(nodes[0].p1[0] - moveX, nodes[0].p1[1] + moveY, nodes[0].p2[0] - moveX, nodes[0].p2[1] + moveY))
  lines.append(cv.create_line(nodes[0].p1[0], nodes[0].p2[1], nodes[1].p2[0], nodes[1].p1[1]))
  ovals.append(cv.create_oval(nodes[1].xy, fill='lightgrey'))
  ovalText.append(cv.create_text(nodes[1].p1[0] + width, nodes[1].p1[1] + width, text=ordermember[1], font='30'))

  #2
  nodes.append(node(nodes[0].p1[0] + moveX, nodes[0].p1[1] + moveY, nodes[0].p2[0] + moveX, nodes[0].p2[1] + moveY))
  lines.append(cv.create_line(nodes[0].p2[0], nodes[0].p2[1], nodes[2].p1[0], nodes[2].p1[1]))
  ovals.append(cv.create_oval(nodes[2].xy, fill='lightgrey'))
  ovalText.append(cv.create_text(nodes[2].p1[0] + width, nodes[2].p1[1] + width, text=ordermember[2], font='30'))

  #3-6
  moveX -= 95
  left = 3
  right = 4

  for parent in range(1, 3):
    nodes.append(node(nodes[parent].p1[0] - moveX, nodes[parent].p1[1] + moveY, nodes[parent].p2[0] - moveX, nodes[parent].p2[1] + moveY))
    lines.append(cv.create_line(nodes[parent].p1[0], nodes[parent].p2[1], nodes[left].p2[0], nodes[left].p1[1]))
    ovals.append(cv.create_oval(nodes[left].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[left].p1[0] + width, nodes[left].p1[1] + width, text=ordermember[left], font='30'))

    nodes.append(node(nodes[parent].p1[0] + moveX, nodes[parent].p1[1] + moveY, nodes[parent].p2[0] + moveX, nodes[parent].p2[1] + moveY))
    lines.append(cv.create_line(nodes[parent].p2[0], nodes[parent].p2[1], nodes[right].p1[0], nodes[right].p1[1]))
    ovals.append(cv.create_oval(nodes[right].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[right].p1[0] + width, nodes[right].p1[1] + width, text=ordermember[right], font='30'))
    left += 2
    right += 2

  #7-14
  moveX -= 60
  moveY += 25
  left = 7
  right = 8

  for parent in range(3, 7):
    nodes.append(node(nodes[parent].p1[0] - moveX, nodes[parent].p1[1] + moveY, nodes[parent].p2[0] - moveX, nodes[parent].p2[1] + moveY))
    lines.append(cv.create_line(nodes[parent].p1[0], nodes[parent].p2[1], nodes[left].p1[0] + width, nodes[left].p1[1]))
    ovals.append(cv.create_oval(nodes[left].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[left].p1[0] + width, nodes[left].p1[1] + width, text=ordermember[left], font='30'))

    nodes.append(node(nodes[parent].p1[0] + moveX, nodes[parent].p1[1] + moveY, nodes[parent].p2[0] + moveX, nodes[parent].p2[1] + moveY))
    lines.append(cv.create_line(nodes[parent].p2[0], nodes[parent].p2[1], nodes[right].p2[0] - width, nodes[right].p1[1]))
    ovals.append(cv.create_oval(nodes[right].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[right].p1[0] + width, nodes[right].p1[1] + width, text=ordermember[right], font='30'))
    left += 2
    right += 2

  #delete unused node
  for i in range(0, len(ordermember)):
    if ordermember[i] == " ":
      cv.delete(ovals[i])
      if i >= 0:
       cv.delete(lines[i-1])

def binary_tree_traversal_handler():

  ordermember = []
  for i in range(0, 15):
    ordermember.append(" ")

  order = [ 
    [-1], [0], [0, 1], [0, 1, 2], [0, 1, 3, 2],
    [0, 1, 3, 4, 2],
    [0, 1, 3, 4, 2, 5],
    [0, 1, 3, 4, 2, 5, 6],
    [0, 1, 3, 7, 4, 2, 5, 6],
    [0, 1, 3, 7, 8, 4, 2, 5, 6], 
    [0, 1, 3, 7, 8, 4, 9, 2, 5, 6], 
    [0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 6],
    [0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 6], 
    [0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6], 
    [0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6, 13],
    [0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6, 13, 14]]

  index = 0
  preorder, inorder = Read()  
  
  for i in preorder:
    ordermember[order[len(preorder)][index]] = i    
    index += 1

  binary_tree_traversal(ordermember)

window.title('binary_tree_traversal')
window.geometry("1400x720")

input1 = tk.Text(window, font='30')
input1.place(x=500, y=2, width=500, height=50)

button1 = tk.Button(window, text='start', command=binary_tree_traversal_handler, font='30')
button1 .place(x=700, y=55)

tk.mainloop()
