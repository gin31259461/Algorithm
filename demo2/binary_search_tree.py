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
  tmp = input_node.get(1.0, "end-1c") 
  read = []
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

  def next_successor(self, node):
    currentNode = node
    while currentNode.left != None:
      currentNode = currentNode.left
    return currentNode

  #inorder
  def deleteNode(self, root, val): 

    if root == None:
      return root

    if root:

      if val < root.val:
        root.left = self.deleteNode(root.left, val)

      elif val > root.val:
        root.right = self.deleteNode(root.right, val)

      else:
      # case only one child or no child
        if root.right == None:
          tmp = root.left
          root = None
          return tmp

        elif root.left == None:
          tmp = root.right
          root = None
          return tmp

      # case two child
        else:
          tmp = self.next_successor(root.right) 
          # connect to next successor
          root.val = tmp.val
          # delete inorder successor
          root.right = self.deleteNode(root.right, tmp.val)
    
    return root

size = 1
def drawtree(root):
    def height(root):
        return 1 + max(height(root.left), height(root.right)) if root else -1
    def jumpto(x, y):
        t.penup()
        t.goto(x, y)
        t.pendown()
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

def draw_search_tree(root):
    def height(root):
        return 1 + max(height(root.left), height(root.right)) if root else -1
    def jumpto(x, y):
        t.penup()
        t.goto(x, y)
        t.pendown()
    def draw(node, x, y, dx):
        global search_data, searchIndex
        if node:
            t.goto(x, y)
            jumpto(x, y-20*size)
            t.fillcolor("yellow")
            t.begin_fill()
            t.circle(20*size)
            t.end_fill()
            jumpto(x, y-10*size)
            t.write(node.val, align='center', font=('Arial', 12*size, 'normal'))
            searchIndex += 1
            if searchIndex == len(search_data):
              return
            jumpto(x, y-20*size)
            
            if search_data[searchIndex] == node.left.val:
              draw(node.left, x-dx, y-60*size, dx/2)
            elif search_data[searchIndex] == node.right.val:
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
    tNode.left = buildTree(inn, pre, inStrt,
                           inIndex - 1)
    tNode.right = buildTree(inn, pre, inIndex + 1,
                            inEnd)
 
    return tNode
 
# This function mainly creates an
# unordered_map, then calls buildTree()
def buldTreeWrap(inn, pre, lenn):
     
    global mp
     
    # Store indexes of all items so that we
    # we can quickly find later
    # unordered_map<char, int> mp;
    for i in range(lenn):
        mp[inn[i]] = i
 
    return buildTree(inn, pre, 0, lenn - 1)

root = TreeNode(0)
def binary_search_tree_build_handler():
  global root
  data = ReadOneLine()
  init = 0

  for i in data:
    if init == 0:
      root = TreeNode(int(i))
      init += 1
    else:
      root.insert(int(i))
  drawtree(root)

search_data = []
searchIndex = 0
def search_data_handler():
  global search_data, searchIndex
  searchIndex = 0
  data = input_search.get()
  search_data = root.search(root, int(data))
  draw_search_tree(root)
  tmp = "Search result : "
  if search_data[len(search_data)-1] != int(data):
    tmp += "Not Found"
  else:
    init = 0
    for i in search_data:
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
  root = root.deleteNode(root, int(data))
  drawtree(root)

def BTS_traversal_build_handler():
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

input_node = tk.Text(window, font='30')
input_node.place(x=500, y=2, width=500, height=50)

input_search = tk.Entry(window, textvariable=search, font='30')
input_search.place(x=1450, y=150, height=30, width=40)

input_delete = tk.Entry(window, textvariable=delete, font='30')
input_delete.place(x=1450, y=200, height=30, width=40)

button_build = tk.Button(window, text='Build', command=binary_search_tree_build_handler, font='30')
button_build .place(x=1500, y=55)

button_order_build = tk.Button(window, text='Order Build', font='30', command=BTS_traversal_build_handler)
button_order_build.place(x=1500, y=100)

button_search = tk.Button(window, text='Search', font='30', command=search_data_handler)
button_search.place(x=1500, y=150)

button_delete = tk.Button(window, text='Delete', font='30', command=delete_node_handler)
button_delete.place(x=1500, y=200)

search_result_label = tk.Label(window, textvariable=search_result, font='100')
search_result_label.place(x=1400, y=500)

cv = tk.Canvas(window, bg='white', height=700, width=1000)
cv.place(x=200, y=100)
t = turtle.RawTurtle(cv)

tk.mainloop()
