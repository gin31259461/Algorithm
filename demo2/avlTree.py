import tkinter as tk
import time
import turtle

def ReadOneLine():

  read = []
  tmp = input_node.get(1.0, "end-1c") 

  for i in tmp.split(", "):
    read.append(int(i))
  return read

class TreeNode(object):
	def __init__(self, val):
		self.val = val
		self.left = None
		self.right = None
		self.height = 1

class AVL_Tree(object):

	def insert(self, root, key):
	
		if not root:
			return TreeNode(key)
		elif key < root.val:
			root.left = self.insert(root.left, key)
		else:
			root.right = self.insert(root.right, key)

		root.height = 1 + max(self.getHeight(root.left), self.getHeight(root.right))

		balance = self.getBalance(root)

		# Case 1 - Left Left
		if balance > 1 and key < root.left.val:
			return self.rightRotate(root)

		# Case 2 - Right Right
		if balance < -1 and key > root.right.val:
			return self.leftRotate(root)

		# Case 3 - Left Right
		if balance > 1 and key > root.left.val:
			root.left = self.leftRotate(root.left)
			return self.rightRotate(root)

		# Case 4 - Right Left
		if balance < -1 and key < root.right.val:
			root.right = self.rightRotate(root.right)
			return self.leftRotate(root)

		return root

	def leftRotate(self, z):

		y = z.right
		T2 = y.left

		# Perform rotation
		y.left = z
		z.right = T2

		# Update heights
		z.height = 1 + max(self.getHeight(z.left),
						self.getHeight(z.right))
		y.height = 1 + max(self.getHeight(y.left),
						self.getHeight(y.right))

		# Return the new root
		return y

	def rightRotate(self, z):

		y = z.left
		T3 = y.right

		# Perform rotation
		y.right = z
		z.left = T3

		# Update heights
		z.height = 1 + max(self.getHeight(z.left),
						self.getHeight(z.right))
		y.height = 1 + max(self.getHeight(y.left),
						self.getHeight(y.right))

		# Return the new root
		return y

	def getHeight(self, root):
		if not root:
			return 0

		return root.height

	def getBalance(self, root):
		if not root:
			return 0

		return self.getHeight(root.left) - self.getHeight(root.right)


def height(root):
    return 1 + max(height(root.left), height(root.right)) if root else -1

def jumpto(x, y):
    t.penup()
    t.goto(x, y)
    t.pendown()

size = 2
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
    t.speed(3); 
    h = height(root)
    jumpto(0, 30*h*size)
    draw(root, 0, 30*h*size, 40*h*size)
    t.hideturtle()

tree = AVL_Tree()
root = None
def insert_value_handler():
  
  global tree, root

  tree = AVL_Tree()
  root = None

  data = ReadOneLine()
  for i in data:
    root = tree.insert(root, int(i))
    drawtree(root)
    time.sleep(1)

window = tk.Tk()
window.title('binary_tree_traversal')
window.geometry("1920x1080")

input_node = tk.Text(window, font='30', )
input_node.config(height=2)
input_node.grid(row=0, column=0, pady=10)

button_build = tk.Button(window, text='Build', font='30', command=insert_value_handler)
button_build.grid(row=0, column=1, sticky="w")

cv = tk.Canvas(window, bg='white', height=900, width=1800)
cv.grid(row=1, column=0, padx=50, columnspan=2)
t = turtle.RawTurtle(cv)

tk.mainloop()
