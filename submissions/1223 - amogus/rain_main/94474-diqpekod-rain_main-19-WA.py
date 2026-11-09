import sys
input = sys.stdin.readline
for case in range(int(input())):
    n, k = map(int, input().split())
    east = []
    north = []
    total = n * k
    for i in range(n):
        x, y, z, a = input().split()
        if a == "E":
            east.append((int(x), int(y)))
        else:
            north.append((int(x), int(y)))
    for i in east:
        for j in north:
            difx = abs(i[0] - j[0])
            dify = abs(i[1] - j[1])
            if difx == dify and difx < k:
                total -= 1
    sys.stdout.write(f"{total}\n")