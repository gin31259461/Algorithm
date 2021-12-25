import tkinter as tk

ovals = []
ovalText = []
lines = []
nodes = []
width = 25
moveX = 200
moveY = 100
currentNode_number = 0

window = tk.Tk()
cv = tk.Canvas(window, bg='white', height=700, width=1000)
cv.place(x=200, y=100)

class Point():
  
  def __init__(self, x0, y0, x1, y1):
    self.p1 = [x0, y0]
    self.p2 = [x1, y1]
    self.xy = [x0, y0, x1, y1]

def Read():
  tmp = input_node.get() 
  read = []
  for i in tmp.split(", "):
    read.append(int(i))
  return read

def drawNode(cmd, data, currentNode):

  global ovals, ovalText, line, width
  if cmd == "init":

    #root
    nodes.append(Point(500, 50, 550, 100))
    lines.append(cv.create_line(0, 0, 0, 0))
    ovals.append(cv.create_oval(nodes[0].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[0].p1[0] + width, nodes[0].p1[1] + width, text=str(data), font='30'))

  elif cmd == "left":

    nodes.append(Point(nodes[currentNode].p1[0] - moveX, nodes[currentNode].p1[1] + moveY, nodes[currentNode].p2[0] - moveX, nodes[currentNode].p2[1] + moveY))
    lines.append(cv.create_line(nodes[currentNode].p1[0] + width, nodes[currentNode].p2[1], nodes[len(nodes)-1].p2[0] - width, nodes[len(nodes)-1].p1[1]))
    ovals.append(cv.create_oval(nodes[len(nodes)-1].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[len(nodes)-1].p1[0] + width, nodes[len(nodes)-1].p1[1] + width, text=data, font='30'))

  elif cmd == "right":

    nodes.append(Point(nodes[currentNode].p1[0] + moveX, nodes[currentNode].p1[1] + moveY, nodes[currentNode].p2[0] + moveX, nodes[currentNode].p2[1] + moveY))
    lines.append(cv.create_line(nodes[currentNode].p2[0]-width, nodes[currentNode].p2[1], nodes[len(nodes)-1].p1[0] + width, nodes[len(nodes)-1].p1[1]))
    ovals.append(cv.create_oval(nodes[len(nodes)-1].xy, fill='lightgrey'))
    ovalText.append(cv.create_text(nodes[len(nodes)-1].p1[0] + width, nodes[len(nodes)-1].p1[1] + width, text=data, font='30'))

  elif cmd == "highlight":
    ovals[currentNode] = cv.create_oval(nodes[currentNode].xy, fill='yellow')
    ovalText[currentNode] = ovalText.append(cv.create_text(nodes[currentNode].p1[0] + width, nodes[currentNode].p1[1] + width, text=str(data), font='30'))

  elif cmd == "highlight_stop":
    ovals[currentNode] = cv.create_oval(nodes[currentNode].xy, fill='red')
    ovalText[currentNode] = ovalText.append(cv.create_text(nodes[currentNode].p1[0] + width, nodes[currentNode].p1[1] + width, text=str(data), font='30'))
    
  elif cmd == "highlight_found":
    ovals[currentNode] = cv.create_oval(nodes[currentNode].xy, fill='green')
    ovalText[currentNode] = ovalText.append(cv.create_text(nodes[currentNode].p1[0] + width, nodes[currentNode].p1[1] + width, text=str(data), font='30'))

  elif cmd == "replace":
    ovals[currentNode] = cv.create_oval(nodes[currentNode].xy, fill='lightgrey')
    ovalText[currentNode] = ovalText.append(cv.create_text(nodes[currentNode].p1[0] + width, nodes[currentNode].p1[1] + width, text=str(data), font='30'))

  elif cmd == "delete":
    cv.delete(ovals[currentNode])
    cv.delete(ovalText[currentNode])
    cv.delete(lines[currentNode])
    cv.delete(nodes[currentNode])

class Node():

  def __init__(self, data, currentNode, moveX, moveY):
    self.left = None
    self.right = None
    self.data = data
    self.currentNode = currentNode 
    self.moveX = moveX
    self.moveY = moveY

  def insert(self, data):
    global nodes, moveX, moveY
    if self.data:
      if data < self.data:
        if self.left == None:
          moveX = self.moveX
          moveY = self.moveY
          drawNode("left", data, self.currentNode)
          self.left = Node(data, len(ovals)-1, self.moveX-40, self.moveY)
        else:
          self.left.insert(data)
      elif data > self.data:
        if self.right == None:
          moveX = self.moveX
          moveY = self.moveY
          drawNode("right", data, self.currentNode)
          self.right = Node(data, len(ovals)-1, self.moveX-40, self.moveY)
        else:
          self.right.insert(data)
    else:
      self.data = data

  def search(self, root, data):
    global nodes, ovals, ovalText, currentNode_number
    res = []
    if root:
      res.append(root.data) 
      drawNode("highlight", root.data, root.currentNode) 
      currentNode_number = root.currentNode
      if data == root.data:
        return res
      elif data > root.data:
        res += self.search(root.right, data)
      elif data < root.data:
        res += self.search(root.left, data)
    return res 

  def inorderTraversal(self, root):
    res = []
    if root:
      res = self.inorderTraversal(root.left)
      res.append(root.data)
      res += self.inorderTraversal(root.right)
    return res 

  def next_successor(self, node):
    currentNode = node
    while currentNode.left != None:
      currentNode = currentNode.left
    return currentNode

  #inorder
  def deleteNode(self, root, data):

    if root == None:
      return root

    if root:

      if data < root.data:
        root.left = self.deleteNode(root.left, data)

      elif data > root.data:
        root.right = self.deleteNode(root.right, data)

      else:
      # case only one child or no child
        if root.left == None and root.right == None:
          drawNode("delete", root.data, root.currentNode)
          root = None 

        elif root.right == None:
          tmp = root.left
          drawNode("delete", root.left.data, root.currentNode)
          root = None
          return tmp

        elif root.left == None:
          tmp = root.right
          drawNode("delete", root.right.data, root.currentNode)
          root = None
          return tmp

      # case two child
        else:
          tmp = self.next_successor(root.right) 

          # connect to next successor
          root.data = tmp.data
          drawNode("replace", root.data, root.currentNode)

          # delete inorder successor
          root.right = self.deleteNode(root.right, tmp.data)
    
    return root


root = Node(0, 0, 0, 0)
def binary_search_tree_handler():

  global cv, ovals, ovalText, lines, moveX, moveY, root, nodes
  data = Read() 
  init = 0
  ovals = []
  nodes = []
  ovalText = []
  lines = []
  moveX = 200
  moveY = 100

  cv = tk.Canvas(window, bg='white', height=700, width=1000)
  cv.place(x=200, y=100)

  for i in data:
    if init == 0:
      root = Node(i, 0, moveX, moveY)
      drawNode("init", i, 0)  
      init = 1
    else:
      root.insert(i)

def search_data_handler():

  global root, ovalText, ovals, currentNode_number

  binary_search_tree_handler()
  data = input_search.get()
  result = root.search(root, int(data))
  tmp = "Search result : "

  if result[len(result)-1] != int(data):
    drawNode("highlight_stop", result[len(result)-1], currentNode_number)
    tmp += "Not Found"

  else:
    drawNode("highlight_found", result[len(result)-1], currentNode_number)
    init = 0
    for i in result:
      if init == 0:
        tmp += "[" + str(i)
        init += 1
      else:
        tmp += ", " + str(i)
    tmp += "]"

  search_result.set(tmp)

def delete_node_handler():
  global root
  data = delete.get() 
  print(root.inorderTraversal(root))
  root.deleteNode(root, int(data))
  print(root.inorderTraversal(root))

window.title('binary_tree_traversal')
window.geometry("1920x1080")

data = tk.StringVar()
search = tk.StringVar()
search_result = tk.StringVar()
delete = tk.StringVar()

input_node = tk.Entry(window, textvariable=data, font='30')
input_node.place(x=500, y=50, height=30, width=500)

input_search = tk.Entry(window, textvariable=search, font='30')
input_search.place(x=1450, y=100, height=30, width=40)

input_delete = tk.Entry(window, textvariable=delete, font='30')
input_delete.place(x=1450, y=150, height=30, width=40)

button_build = tk.Button(window, text='Build', command=binary_search_tree_handler, font='30')
button_build .place(x=1500, y=55)

button_search = tk.Button(window, text='Search', font='30', command=search_data_handler)
button_search.place(x=1500, y=100)

button_delete = tk.Button(window, text='Delete', font='30', command=delete_node_handler)
button_delete.place(x=1500, y=150)

search_result_label = tk.Label(window, textvariable=search_result, font='100')
search_result_label.place(x=1400, y=500)

tk.mainloop()
