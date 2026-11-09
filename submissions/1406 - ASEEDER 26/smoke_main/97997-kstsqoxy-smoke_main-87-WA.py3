n1=int(input())
for i in range(n1):
	n2,cd = map(int,input().split())
	time = list(map(int,input().split()))
	cur = 1
	for i in range(1,n2):
		if ((time[i]-time[i-1])<cd):
			cur=0
	if (cur):
		print("YES")
	else:
		print("NO")
	
		
		