import sys
import bisect
from collections import defaultdict

for _ in range(int(input())):
    N,K = map(int,input().split())
    drones = []
    for _ in range(N):
        X,Y,Z,D = input().split()
        drones.append((int(X),int(Y),D))
    
    east = defaultdict(list)
    for X, Y, D in drones:
        if D == 'E':
            east[X + Y].append(Y)
    for ys in east.values():
        ys.sort()

    ans = N*K
    for X, Y, D in drones:
        if D == 'N':
            ys = east[X + Y]
            ans -= bisect.bisect_right(ys, Y + K - 1) - bisect.bisect_left(ys, Y)
    print(ans)