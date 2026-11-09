from math import isqrt

def find(parent, x):
    root = x
    while parent[root] != root:
        root = parent[root]

    while parent[x] != x:
        nxt = parent[x]
        parent[x] = root
        x = nxt

    return root

t = int(input())
for _ in range(t):
  n,m,q = map(int,input().split())
  quakes = []
  for _ in range(q):
    quakes.append(list(map(int,input().split())))
  quakes = quakes[::-1]
  parent = [[y for y in range(m+1)] for _ in range(n)]
  pos = [0] * n
  for x in range(n):
    pos[x] = [0] * m
  
  for quake in quakes:
    rc = quake[0]
    cc = quake[1]
    p = quake[2]
    p2 = p**2
    startr = max(0,rc-p)
    endr = min(rc+p+1,n)

    for r in range(startr,endr):
      rchange = rc-r
      cchange = isqrt(p2-rchange**2)
      startc = cc-cchange
      endc = cc + cchange + 1
      c = find(parent[r], startc)
      while c < endc:
        power = max(0,p2 - ((rc-r)**2 + (cc-c)**2) + 1)
        pos[r][c] = power
        parent[r][c] = find(parent[r], c+1)
        c = find(parent[r], c)
  for line in pos:
    print(*line)
