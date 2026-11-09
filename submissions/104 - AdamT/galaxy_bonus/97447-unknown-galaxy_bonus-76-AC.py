#!/usr/bin/env python3

import sys
sys.setrecursionlimit(10**6)

T = int(input())

v = []

def solve(a, x, y, n, m, id):
    global r, v
    ds = [(1,0), (-1,0), (0,1), (0,-1)]
    v[x][y] = id
    for dx, dy in ds:
        nx, ny = x + dx, y + dy
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue
        if a[x][y] != '.' and a[nx][ny] != '.' and a[x][y] != a[nx][ny]:
            continue
        if v[nx][ny] != -1:
            continue
        solve(a, nx, ny, n, m, id)
        
    

for _ in range(T):
    n, m, q = [int(n) for n in input().split()]
    a = [[c for c in input()] for _ in range(n)]
    r = [[False for _ in l] for l in a]
    v = [[-1 for _ in l] for l in a]
    id = 0
    for x in range(n):
        for y in range(m):
            if v[x][y] == -1:
                solve(a, x, y, n, m, id)
                id += 1
    for _ in range(q):
        x, y, tx, ty = [int(n) for n in input().split()]
        if v[x][y] == v[tx][ty]:
            print("YES")
        else:
            print("NO")
