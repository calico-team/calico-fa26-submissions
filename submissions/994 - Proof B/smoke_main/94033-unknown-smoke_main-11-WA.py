def testcase():
	inputs = input().split(" ")
	n = int(inputs[0])
	r = int(inputs[1])
	times = [int(rt) for rt in input().split()]
	for i, time in enumerate(times):
		if time // r <= i:
			print("NO")
			return
	print("YES")

T = int(input())
for _ in range(T):
	testcase()