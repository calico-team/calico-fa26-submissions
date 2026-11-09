import sys

input_ = sys.stdin.readline

I = []
t = int(input_())

for _ in range(t):
    n, k = (int(v) for v in input_().split())
    L = [[int(x), int(y), int(z), d] for x, y, z, d in [input_().split() for _ in range(n)]]

    s = 0
    for _ in range(k):
        s += len({(x[0], x[1]): x for x in L})

        for i, d in enumerate(L):
            if d[3] == "N":
                L[i][1] += 1
            elif d[3] == "E":
                L[i][0] += 1

    print(s)