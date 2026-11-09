def testcase():
	inputs = input().split(" ")
	n = int(inputs[0])
	r = int(inputs[1])
	times = [int(rt) for rt in input().split()]
	c = 2
	lc = 0
	for i, time in enumerate(times):
		g = (time - lc) // r
		c = min(c + g, 2)

		if c == 2:
			lc = time
		else:
			lc += g * r

		if c == 0:
			print("NO")
			return

		c -= 1
	print("YES")

T = int(input())
for _ in range(T):
	testcase()