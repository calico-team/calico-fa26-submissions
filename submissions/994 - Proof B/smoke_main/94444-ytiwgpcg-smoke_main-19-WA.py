def testcase():
	inputs = input().split(" ")
	n = int(inputs[0])
	r = int(inputs[1])
	times = [int(rt) for rt in input().split()]
	c = 2
	lc = 0
	for i, time in enumerate(times):
		c = min(c + (time - lc) // r, 2)
		if c == 0:
			print("NO")
			return
		c -= 1
		lc = time
	print("YES")

T = int(input())
for _ in range(T):
	testcase()