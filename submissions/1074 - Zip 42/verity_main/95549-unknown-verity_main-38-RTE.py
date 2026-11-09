import sys
input = sys.stdin.readline
print = sys.stdout.write
t = int(input())
for _ in range(t):
	n, k = map(int, input().strip().split())
	A = list(input().strip().split())
	word = [None] * n
	for i in A:
		sys.stdout.write(i*n+'\n')
		sys.stdout.flush()
		inp = list(input().strip())
		for i in range(n):
			if inp[i] != '_':
				word[i] = inp[i]
	print(''.join(word)+'\n')
	sys.stdout.flush()
	input()
