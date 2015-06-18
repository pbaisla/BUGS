import requests

last1x, last1y = 1, 1
last2x, last2y = 15, 15

def mov(m, p):
	global last1x, last1y, last2x, last2y
	for i in range(15):
		for j in range(15):
			if (((last1x == i) and (last1y == j)) or ((last2x == i) and (last2y == j))):
				continue
			else:
				board[i][j] = board[i][j].lower()
	x, y = m.split('|')
	x = int(x) -1
	y = int(y) -1
	if p == 'O':
		last1x, last1y = x, y
	elif p == 'J':
		last2x, last2y = x, y
	board[x][y] = p

def printboard(board):
	for row in board:
		for square in row:
			print(square, end=' ')
		print('')

player1 = 'http://127.0.0.1:9000/'
player2 = 'http://127.0.0.1:3000/'

board = [['_' for i in range(15)] for j in range(15)]

print("player1 pinged", requests.get(player1 + 'ping').json())
print("player2 pinged", requests.get(player2 + 'ping').json())

print("player1 start", requests.get(player1 + 'start?y=1|1&o=15|15&g=15').json())
print("player2 start", requests.get(player2 + 'start?y=15|15&o=1|1&g=15').json())

mov("1|1", 'O')
move = "15|15"

while(True):
	print("player2", move)
	mov(move, 'J')
	printboard(board)
	if(last1x == last2x) and (last1y == last2y):
		print("player 2 wins")
		break
	# send move to player1
	move = requests.get(player1 + 'play?m=' + move).json()["m"]
	print("player1", move)
	mov(move, 'O')
	printboard(board)
	if(last1x == last2x) and (last1y == last2y):
		print("player 1 wins")
		break
	# send move to player2
	move = requests.get(player2 + 'play?m=' + move).json()["m"]


#response = requests.get(url)
#data = response.json()
#print(data)