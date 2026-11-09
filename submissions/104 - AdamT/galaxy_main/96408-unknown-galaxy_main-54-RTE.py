#!/usr/bin/env python3

T = int(input())

r = []
v = []

def solve(a, x, y, n, m):
    global r, v
    if x < 0 or x >= n or y < 0 or y >= m:
        return
    if v[x][y]:
        return
    v[x][y] = True
    r[x][y] = True
    ds = [(1,0), (-1,0), (0,1), (0,-1)]
    for dx, dy in ds:
        nx, ny = x + dx, y + dy
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue
        if a[x][y] != '.' and a[nx][ny] != '.' and a[x][y] != a[nx][ny]:
            continue
        solve(a, nx, ny, n, m)
        
    

for _ in range(T):
    n, m, q = [int(n) for n in input().split()]
    a = [[c for c in input()] for _ in range(n)]
    r = [[False for _ in l] for l in a]
    v = [[False for _ in l] for l in a]
    solve(a, n-1, m-1, n, m)
    for _ in range(q):
        x, y, tx, ty = [int(n) for n in input().split()]
        if r[x][y]:
            print("YES")
        else:
            print("NO")
