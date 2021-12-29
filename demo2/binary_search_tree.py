import tkinter as tk
import turtle

def ReadTwoLine():
    
  readline = []
  preorder = []
  inorder = []

  tmp = input_node.get(1.0, "end-1c")

  for i in tmp.split("\n"):
    readline.append(i)

  for i in readline[0].split(", "):
    preorder.append(i)

  for i in readline[1].split(", "):
    inorder.append(i)

  return preorder, inorder

def ReadOneLine():

  read = []
  tmp = input_node.get(1.0, "end-1c") 

  for i in tmp.split(", "):
    read.append(int(i))
  return read

class TreeNode:

  def __init__(self, val, left=None, right=None):
    self.val = val
    self.left = left
    self.right = right

  def insert(self, val):
    if self.val:
      if val < self.val:
        if self.left == None:
          self.left = TreeNode(val) 
        else:
          self.left.insert(val)
      elif val > self.val:
        if self.right == None:
          self.right = TreeNode(val)
        else:
          self.right.insert(val)
    else:
      self.val = val

  def search(self, node, val):
    res = []
    if node:
      res.append(node.val) 
      if val == node.val:
        return res
      elif val > node.val:
        res += self.search(node.right, val)
      elif val < node.val:
        res += self.search(node.left, val)
    return res 

  def delete(self, root, val):
     
    if root is None:
      return root
     
    if val < root.val:
      root.left = self.delete(root.left, val)
      return root
     
    elif(val > root.val):
      root.right = self.delete(root.right, val)
      return root
     
    if root.left is None and root.right is None:
      return None
     
    # case one of the children is empty
     
    if root.left is None:
      temp = root.right
      root = None
      return temp
     
    elif root.right is None:
      temp = root.left
      root = None
      return temp
     
    # case both children exist
     
    succParent = root
     
    # Find Successor
     
    succ = root.right
     
    while succ.left != None:
      succParent = succ
      succ = succ.left
     
    # delete successor
    if succParent != root:
      succParent.left = succ.right
    else:
      succParent.right = succ.right
     
    # Copy Successor Data to root
     
    root.val = succ.val
     
    return root

def height(root):
    return 1 + max(height(root.left), height(root.right)) if root else -1

def jumpto(x, y):
    t.penup()
    t.goto(x, y)
    t.pendown()

size = 1
def drawtree(root):

    def draw(node, x, y, dx):
        if node:
            t.goto(x, y)
            jumpto(x, y-20*size)
            draw(node.left, x-dx, y-60*size, dx/2)
            jumpto(x, y-20*size)
            t.fillcolor("grey")
            t.begin_fill()
            t.circle(20*size)
            t.end_fill()
            jumpto(x, y-10*size)
            t.write(node.val, align='center', font=('Arial', 12*size, 'normal'))
            jumpto(x, y-20*size)
            draw(node.right, x+dx, y-60*size, dx/2)
    t.clear()
    t.showturtle()
    t.speed(0); 
    h = height(root)
    jumpto(0, 30*h*size)
    draw(root, 0, 30*h*size, 40*h*size)
    t.hideturtle()

fillColor = "grey"
def draw_search_tree(root):

    def draw(node, x, y, dx):

        global searchVal, searchIndex, fillColor

        if node:
            t.goto(x, y)
            jumpto(x, y-20*size)
            t.fillcolor(fillColor)
            t.begin_fill()
            t.circle(20*size)
            t.end_fill()
            jumpto(x, y-10*size)
            t.write(node.val, align='center', font=('Arial', 12*size, 'normal'))
            searchIndex += 1
            if searchIndex == len(searchVal):
              return
            jumpto(x, y-20*size)
            
            if searchIndex == len(searchVal):
              return

            if node.left != None:
              if searchVal[searchIndex] == node.left.val:
                draw(node.left, x-dx, y-60*size, dx/2)

            if searchIndex == len(searchVal):
              return

            if node.right != None:
              if searchVal[searchIndex] == node.right.val:
                draw(node.right, x+dx, y-60*size, dx/2)

    t.showturtle()
    t.speed(0); 
    h = height(root)
    jumpto(0, 30*h*size)
    draw(root, 0, 30*h*size, 40*h*size)
    t.hideturtle()

preIndex = 0
mp = {}
def buildTree(inn, pre, inStrt, inEnd):
     
    global preIndex, mp
 
    if (inStrt > inEnd):
      return None
 
    # Pick current node from Preorder traversal
    # using preIndex and increment preIndex
    curr = pre[preIndex]
    preIndex += 1
    tNode = TreeNode(curr)
 
    # If this node has no children then return
    if (inStrt == inEnd):
      return tNode
 
    # Else find the index of this
    # node in Inorder traversal
    inIndex = mp[curr]
 
    # Using index in Inorder traversal,
    # construct left and right subtress
    tNode.left = buildTree(inn, pre, inStrt, inIndex - 1)
    tNode.right = buildTree(inn, pre, inIndex + 1, inEnd)
 
    return tNode
 
# use this function call buildTree
def buldTreeWrap(inn, pre, lenn):
     
    global mp
    
    # store inorder index of value
    # map <char, int> 
    for i in range(lenn):
        mp[inn[i]] = i
 
    return buildTree(inn, pre, 0, lenn - 1)

root = TreeNode(0)
def binary_search_tree_build_handler():

  global root

  init = 0

  data = ReadOneLine()

  for i in data:
    if init == 0:
      root = TreeNode(int(i))
      init += 1
    else:
      root.insert(int(i))

  drawtree(root)

searchVal = []
preSearchVal = [None]
searchIndex = 0
def search_value_handler():

  global searchVal, searchIndex, preSearchVal, fillColor

  searchIndex = 0
  fillColor = "grey"
  tmp = "Search result : "

  data = input_search.get()
  reg = root.search(root, int(data))
  searchVal = preSearchVal 
  draw_search_tree(root)
  searchVal = reg

  searchIndex = 0
  fillColor = "yellow"

  draw_search_tree(root)
  preSearchVal = searchVal

  if searchVal[len(searchVal)-1] != int(data):
    searchIndex = 0
    tmp += "Not Found"
    fillColor = "red"
    draw_search_tree(root)
  else:
    searchIndex = 0
    fillColor = "green"
    draw_search_tree(root)
    init = 0
    for i in searchVal:
      if init == 0:
        tmp += "[" + str(i)
        init += 1
      else:
        tmp += ", " + str(i)
    tmp += "]"
  search_result.set(tmp)

def delete_node_handler():

  global root

  data = input_delete.get() 
  root.delete(root, int(data))
  drawtree(root)

def traversal_build_tree_handler():

  global root, preIndex, mp

  preIndex = 0
  mp = {}

  preorder, inorder = ReadTwoLine()
  root = buldTreeWrap(inorder, preorder, len(inorder))
  drawtree(root)

window = tk.Tk()
window.title('binary_tree_traversal')
window.geometry("1920x1080")

data = tk.StringVar()
search = tk.StringVar()
search_result = tk.StringVar()
delete = tk.StringVar()

input_node = tk.Text(window, font='30', )
input_node.config(height=2)
input_node.grid(row=0, column=0, pady=10)

input_search = tk.Entry(window, textvariable=search, font='30')
input_search.config(width=4)
input_search.grid(row=3, column=2)

input_delete = tk.Entry(window, textvariable=delete, font='30')
input_delete.config(width=4)
input_delete.grid(row=4, column=2)

button_build = tk.Button(window, text='Build', command=binary_search_tree_build_handler, font='30')
button_build.grid(row=1, column=3, sticky="w")

button_order_build = tk.Button(window, text='Order Build', font='30', command=traversal_build_tree_handler)
button_order_build.grid(row=2, column=3, sticky="w")

button_search = tk.Button(window, text='Search', font='30', command=search_value_handler)
button_search.grid(row=3, column=3, sticky="w")

button_delete = tk.Button(window, text='Delete', font='30', command=delete_node_handler)
button_delete.grid(row=4, column=3, sticky="w")

search_result_label = tk.Label(window, textvariable=search_result, font='100')
search_result_label.config(width=30)
search_result_label.grid(row=5, column=1)

cv = tk.Canvas(window, bg='white', height=800, width=1200)
cv.grid(row=1, column=0, padx=50, rowspan=5)
t = turtle.RawTurtle(cv)

tk.mainloop()
