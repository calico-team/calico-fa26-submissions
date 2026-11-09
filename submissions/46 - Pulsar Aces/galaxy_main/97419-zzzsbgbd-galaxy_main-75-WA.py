# for _ in range(int(input())):
# 	N,M,Q = map(int, input().split())
# 	grid=[]
# 	for _ in range(N):
# 		grid.append(list(input()))
# 	comps=dict()
# 	poss=list(range(M*N))
# 	stack=[]
# 	cnum=0
# 	while poss!=[]:
# 		stack.append(poss[0])
# 		while stack!=[]:
# 			a=stack[0]
# 			stack.remove(a)
# 			poss.remove(a)
# 			comps[a]=cnum
# 			c=grid[int(a//M)][a%M]
# 			d0=[a-M,a-1 if a%M>0 else -1,a+1 if a%M<M-1 else -1,a+M]
# 			for d1 in d0:
# 				if 0<=d1<M*N:
# 					d=grid[int(d1//M)][d1%M]
# 					if c=="." or d=="." or c==d:
# 						if d1 in poss and d1 not in stack:
# 							stack.append(d1)
# 		cnum+=1
# 	for _ in range(Q):
# 		R0,C0,R1,C1=map(int, input().split())
# 		print("YES" if comps[R0*M+C0]==comps[R1*M+C1] else "NO")

def inv(k):
	return 'B' if k == 'R' else 'R'
def minisolve(n, m, grid):
	a, b, c, d = map(int, input().split())
	seen = set([200 * a + b])
	stack = [[a, b, 'R']]
	while len(stack) > 0:
		i = stack.pop()
		
		possible = [
			[i[0], i[1] + 1, i[2]],
			[i[0], i[1] - 1, i[2]],
			[i[0] + 1, i[1], i[2]],
			[i[0] - 1, i[1], i[2]],
		]
		if grid[i[0]][i[1]] == '.':
			possible.extend([
				[i[0], i[1] + 1, inv(i[2])],
				[i[0], i[1] - 1, inv(i[2])],
				[i[0] + 1, i[1], inv(i[2])],
				[i[0] - 1, i[1], inv(i[2])],
			])
		for k in possible:
			if k[0] < 0 or k[0] >= n or k[1] < 0 or k[1] >= m:
				continue
			if (not 200 * k[0] + k[1] in seen) and grid[k[0]][k[1]] != inv(k[2]):
				stack.append(k)
				seen.add(200 * k[0] + k[1])
			if k[0] == c and k[1] == d:
				print("YES")
				return
	print("NO")
def solve():
	n, m, q = map(int, input().split())
	grid = []
	for i in range(n):
		grid.append(list(input()))
	for i in range(q):
		minisolve(n, m, grid)

for i in range(int(input())):
	solve()
