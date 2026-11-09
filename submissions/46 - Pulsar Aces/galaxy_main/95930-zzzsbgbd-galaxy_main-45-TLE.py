for _ in range(int(input())):
	N,M,Q = map(int, input().split())
	grid=[]
	for _ in range(N):
		grid.append(list(input()))
	comps=dict()
	poss=list(range(M*N))
	stack=[]
	cnum=0
	while poss!=[]:
		stack.append(poss[0])
		while stack!=[]:
			a=stack[0]
			stack.remove(a)
			poss.remove(a)
			comps[a]=cnum
			c=grid[int(a//M)][a%M]
			d0=[a-M,a-1 if a%M>0 else -1,a+1 if a%M<M-1 else -1,a+M]
			for d1 in d0:
				if 0<=d1<M*N:
					d=grid[int(d1//M)][d1%M]
					if c=="." or d=="." or c==d:
						if d1 in poss and d1 not in stack:
							stack.append(d1)
		cnum+=1
	for _ in range(Q):
		R0,C0,R1,C1=map(int, input().split())
		print("YES" if comps[R0*M+C0]==comps[R1*M+C1] else "NO")