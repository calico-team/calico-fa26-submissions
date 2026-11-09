import sys, bisect
input = sys.stdin.readline
for case in range(int(input())):
    n, k = map(int, input().split())
    east = []
    north = {}
    total = n * k
    for i in range(n):
        x, y, z, a = input().split()
        x = int(x)
        y = int(y)
        if a == "E":
            east.append((x, y))
        else:
            try:
                north[x + y].append(x)
            except:
                north[x + y] = [x]
    for i in north.keys():
        north[i].sort()
    for i in east:
        try:
            possible = north[sum(i)]
            total -= bisect.bisect_right(possible, i[0] + k - 1) - bisect.bisect_right(possible, i[0])
        except:
            pass
    sys.stdout.write(f"{total}\n")