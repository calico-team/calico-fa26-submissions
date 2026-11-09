for _ in range(int(input())):
	N,M,Q=map(int, input().split())
	meters=[0 for _ in range(N*M)]
	for _ in range(Q):
		R,C,P=map(int, input().split())
		for i in range(N):
			for j in range(M):
				p=P**2-(i-R)**2-(j-C)**2+1
				if p>0:
					meters[i*M+j]=p
	meters=list(map(str,meters))
	for i in range(N):
		print(" ".join(meters[i*M:i*M+M]))