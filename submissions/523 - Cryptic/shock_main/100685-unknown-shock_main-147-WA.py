t = int(input())
for _ in range(t):
  n,m,q = map(int,input().split())
  quakes = []
  for _ in range(q):
    quakes.append(list(map(int,input().split())))
  quakes = quakes[::-1]
  pos = [0] * n
  for x in range(n):
    pos[x] = [0] * m
  for quake in quakes:
    rc = quake[0]
    cc = quake[1]
    p = quake[2]
    p2 = p**2
    startr = max(0,rc-p)
    endr = min(rc+p+1,m+1)
    startc = max(0,cc-p)
    endc = min(cc+p+1,n+1)
    for r in range(startr,endr):
      for c in range(startc,endc):
        if pos[r][c] == 0:
          power = max(0,p2 - ((rc-r)**2 + (cc-c)**2) + 1)
          pos[r][c] = power
  for line in pos:
    print(*line)
