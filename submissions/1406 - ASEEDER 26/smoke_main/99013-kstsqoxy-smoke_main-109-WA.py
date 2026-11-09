n1=int(input())
for i in range(n1):
	n2,cd = map(int,input().split())
	time = list(map(int,input().split()))
	cur = 1
	for j in range(1,n2):
		if (time[j]-time[j-1])<cd:
			cur=0
			break
	if cur:
		print("YES")
	else:
		print("NO")
