# import sys
# input = sys.stdin.readline
# print = sys.stdout.write
# t = int(input())
# for _ in range(t):
# 	n, k = map(int, input().strip().split())
# 	A = list(input().strip().split())
# 	word = [None] * n
# 	corr = False
# 	for i in A:
# 		sys.stdout.write(i*n+'\n')
# 		sys.stdout.flush()
# 		inp = list(input().strip())
# 		if inp == list('CORRECT'):
# 			corr = True
# 			break
# 		for i in range(n):
# 			if inp[i] != '_':
# 				word[i] = inp[i]
# 	if corr:
# 		continue
#
# 	print(''.join(word)+'\n')
# 	sys.stdout.flush()
# 	input()

from collections import deque
for _ in range(int(input())):
	rows, columns, earthquakes = map(int, input().split())


	def check(r, c):
		if 0 <= r < rows and 0 <= c < columns:
			return True
		return False


	grid = [[0]*columns for _ in range(rows)]
	for _ in range(earthquakes):
		row, column, power = map(int, input().split())
		grid[row][column] = power*power+1
		queue = deque([(row, column)])
		visited = {(row, column)}
		while queue:
			rowr, columnn = queue.popleft()
			for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1),):
				nr = rowr+dr
				nc = columnn+dc
				if check(nr, nc) and (nr, nc) not in visited:
					val = max(power**2 - (abs(nr-rowr)**2+abs(nc-columnn)**2) + 1, 0)
					if val > 0:
						grid[nr][nc] = val
						queue.append((nr, nc))
					visited.add((nr, nc))
	for i in grid:
		print(*i)
