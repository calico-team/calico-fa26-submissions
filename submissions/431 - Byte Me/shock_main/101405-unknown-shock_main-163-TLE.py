from math import isqrt
 
 
def find(x, parent):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x
 
 
T = int(input())
 
for _ in range(T):
    N, M, Q = map(int, input().split())
    earthquakes = []
 
    for _ in range(Q):
        R, C, P = map(int, input().split())
        earthquakes.append((R, C, P))
 
    size = N * M
    grid = [0] * size
    parent = list(range(size + 1))
 
    for R, C, P in reversed(earthquakes):
        power = P * P
 
        for r in range(R - P, R + P + 1):
            dr = (r - R) ** 2
            width = isqrt(power - dr)
            start = r * M + C - width
            end = r * M + C + width
 
            x = find(start, parent)
 
            while x <= end:
                c = x % M
                grid[x] = power - dr - (c - C) ** 2 + 1
                parent[x] = find(x + 1, parent)
                x = parent[x]
 
    for r in range(N):
        start = r * M
        print(*grid[start:start + M])