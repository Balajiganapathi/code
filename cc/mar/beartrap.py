# The example usage is shown at the bottom of the program.

SLEEP_TIME = 0.01 # time waited after draw()
ALWAYS_DRAW = True # "True" if you want to run draw() automatically after each cat() and block()
N = 20 # the size of the grid
where_cat = (0, 0)
blocked = []

def clear():
	global where_cat
	global blocked
	where_cat = (0, 0)
	blocked = []

def inside(row, col):
	if abs(row) >= N:
		return False
	if row <= 0:
		return -N - row + 1 <= col and col < N
	return -N + 1 <= col and col < N - row

def areAdjacent(A, B):
	if A[0] == B[0]:
		return abs(A[1] - B[1]) == 1
	if A[1] == B[1]:
		return abs(A[0] - B[0]) == 1
	return A == (B[0]+1, B[1]-1) or B == (A[0]+1, A[1]-1)

def draw():
	def char(row, col):
		assert(inside(row, col))
		if (row, col) == where_cat:
			return "c"
		if blocked.count((row, col)) == 1:
			return "#"
		return "." if col % 2 == 0 else ","
	for row in range(-N+1, N):
		for repeat in range(abs(row)):
			print(" ", end = "")
		if row <= 0:
			for col in range(-N - row + 1, N):
				print(char(row,col) + " ", end = "")
		else:
			for col in range(-N + 1, N - row):
				print(char(row,col) + " ", end = "")
		print("")
	print("")
	import time
	time.sleep(SLEEP_TIME)

def my_error(command, message):
	print("error in " + command + ": " + message)
	exit(1)

def my_warning(command, message):
	print("warning in " + command + ": " + message)

def cat(row, col):
	global where_cat
	command = "cat(" + str(row) + "," + str(col) + ")"
	if not inside(row, col):
		my_error(command, "cat can't move to a cell outside the grid.")
	if blocked.count((row, col)):
		my_error(command, "cat can't move to a blocked cell.")
	if not areAdjacent(where_cat, (row, col)):
		my_warning(command, "cat moved between two cells that aren't adjacent.")
	where_cat = (row, col)
	if ALWAYS_DRAW:
		draw()

def block(row, col):
	global blocked
	command = "block(" + str(row) + "," + str(col) + ")"
	if not inside(row, col):
		my_error(command, "you can't block a cell outside the grid.")
	if blocked.count((row, col)):
		my_error(command, "you can't block a cell that is already blocked.")
	if where_cat == (row, col):
		my_error(command, "command ignored - you can't block a cell that contains the cat.")
	blocked.append((row, col))
	if ALWAYS_DRAW:
		draw()

"""
README

You can save this file as visualizer.py and run it in a terminal with a command:
	python3 visualizer.py

You can use functions:

1) cat(r,c) - Move the cat to (r,c). Prints warning if (r,c) isn't adjacent
		to the previous cell where the cat was. Terminates with error if
		the cell (r,c) is blocked or is outside the grid.

2) block(r,c) - Block the cell (r,c). Terminates with error if the cell (r,c)
		is already blocked, is outside the grid or it contains the cat.

3) clear() - Clears the grid. The cat will be in the cell (0,0).

4) draw() - Draws the grid and waits for SLEEP_TIME seconds (0.3 by default).

By default functions cat() and block() run the function draw() automatically.
To turn it off, use a command "ALWAYS_DRAW = False". You can turn it on
again with "ALWAYS_DRAW = True" if you want.

If you want to change the time waited after each draw(), use "SLEEP_TIME = X"
where X denotes the new time in seconds.

You can change the grid size with e.g. "N = 15".

You can modify this file in any way you want, but you can't share
any modifications with other participants.

See the example usage below.
"""

clear()
cat(0, -1)
block(0, -2)
cat(-1, -1)
block(-2, -1)
cat(-1, -2)
block(-2, -2)
cat(-1, -3)
block(-2, -3)
cat(-1, -4)
block(-2, -4)
cat(-1, -5)
block(-2, -5)
cat(-1, -6)
block(-7, -12)
cat(-2, -6)
block(-8, -11)
cat(-2, -7)
block(-6, -13)
cat(-2, -8)
block(-5, -14)
cat(-3, -8)
block(-11, -8)
cat(-3, -9)
block(-3, -16)
cat(-4, -9)
block(-10, -9)
cat(-4, -10)
block(-9, -10)
cat(-4, -11)
block(-3, -14)
cat(-4, -12)
block(-4, -13)
cat(-5, -12)
block(-6, -12)
cat(-5, -13)
block(-4, -15)
cat(-4, -14)
block(-3, -15)
cat(-5, -13)
block(-5, -12)
clear()
cat(-1, 1)
block(-2, 2)
cat(-2, 1)
block(-3, 1)
cat(-3, 2)
block(-4, 2)
cat(-4, 3)
block(-5, 3)
cat(-5, 4)
block(-6, 4)
cat(-6, 5)
block(-7, 5)
cat(-7, 6)
block(-19, 12)
cat(-8, 7)
block(-19, 13)
cat(-9, 8)
block(-19, 14)
cat(-10, 9)
block(-19, 15)
cat(-11, 10)
block(-19, 10)
cat(-12, 10)
block(-19, 17)
cat(-13, 10)
block(-19, 11)
cat(-14, 11)
block(-19, 18)
cat(-15, 12)
block(-17, 15)
cat(-16, 13)
block(-17, 14)
cat(-17, 13)
block(-18, 13)
cat(-18, 14)
block(-18, 16)
cat(-18, 15)
block(-19, 16)
cat(-18, 14)
block(-17, 13)
clear()
cat(0, 1)
block(0, 2)
cat(-1, 2)
block(-1, 3)
cat(-2, 3)
block(-2, 4)
cat(-3, 4)
block(-3, 5)
cat(-4, 5)
block(-4, 6)
cat(-5, 6)
block(-5, 7)
cat(-6, 7)
block(-12, 19)
cat(-6, 8)
block(-11, 19)
cat(-7, 9)
block(-13, 19)
cat(-7, 10)
block(-10, 19)
cat(-8, 11)
block(-16, 19)
cat(-8, 12)
block(-8, 19)
cat(-9, 13)
block(-15, 19)
cat(-9, 14)
block(-14, 19)
cat(-9, 15)
block(-8, 17)
cat(-9, 16)
block(-9, 17)
cat(-10, 17)
block(-11, 18)
cat(-10, 18)
block(-9, 19)
cat(-9, 18)
block(-8, 18)
cat(-10, 18)
block(-10, 17)
clear()
cat(0, 1)
block(0, 2)
cat(-1, 2)
block(-1, 3)
cat(-2, 3)
block(-2, 4)
cat(-3, 4)
block(-3, 5)
cat(-4, 5)
block(-4, 6)
cat(-5, 6)
block(-5, 7)
cat(-6, 7)
block(-12, 19)
cat(-7, 8)
block(-13, 19)
cat(-8, 9)
block(-14, 19)
cat(-9, 10)
block(-15, 19)
cat(-9, 11)
block(-17, 19)
cat(-10, 12)
block(-10, 19)
cat(-10, 13)
block(-16, 19)
cat(-11, 14)
block(-15, 18)
cat(-11, 15)
block(-10, 16)
cat(-11, 16)
block(-11, 17)
cat(-12, 17)
block(-13, 17)
cat(-12, 18)
block(-11, 18)
cat(-13, 18)
block(-12, 17)
cat(-14, 18)
block(-14, 17)
clear()
cat(0, -1)
block(0, -2)
cat(-1, -1)
block(-2, -1)
cat(-1, -2)
block(-2, -2)
cat(-1, -3)
block(-2, -3)
cat(-1, -4)
block(-2, -4)
cat(-1, -5)
block(-2, -5)
cat(-1, -6)
block(-7, -12)
cat(-1, -7)
block(-6, -13)
cat(-2, -7)
block(-8, -11)
cat(-2, -8)
block(-5, -14)
cat(-3, -8)
block(-11, -8)
cat(-4, -8)
block(-10, -9)
cat(-5, -8)
