import tkinter as tk
import turtle

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

class TreeNode:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

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
            jumpto(x, y-20)
            draw(node.left, x-dx, y-60, dx/2)
            jumpto(x, y-20)
            t.fillcolor("grey")
            t.begin_fill()
            t.circle(20)
            t.end_fill()
            jumpto(x, y-10)
            t.write(node.val, align='center', font=('Arial', 12, 'normal'))
            jumpto(x, y-20)
            draw(node.right, x+dx, y-60, dx/2)

    t.showturtle()
    t.speed(0); 
    h = height(root)
    jumpto(0, 30*h)
    draw(root, 0, 30*h, 40*h)
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

def binary_tree_traversal_handler():
  global preIndex, mp
  preIndex = 0
  mp = {}
  preorder, inorder = Read() 
  root = buldTreeWrap(inorder, preorder, len(inorder)) 
  drawtree(root)

window = tk.Tk()
window.title('binary_tree_traversal')
window.geometry("1400x720")

input1 = tk.Text(window, font='30')
input1.place(x=500, y=2, width=500, height=50)

button1 = tk.Button(window, text='start', command=binary_tree_traversal_handler, font='30')
button1 .place(x=700, y=55)

cv = tk.Canvas(window, bg='white', height=700, width=1000)
cv.place(x=200, y=100)
t = turtle.RawTurtle(cv)

tk.mainloop()
