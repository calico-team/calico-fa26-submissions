t = int(input())
for _ in range(t):
  n,k = map(int,input().split())
  drones = []
  eastSums = {}
  northSums = {}
  for _ in range(n):
    x,y,z,d = input().split()
    x,y,z=int(x),int(y),int(z)
    drones.append([x,y,z,d])
    ttl = x + y
    if d == 'E':
      if ttl not in eastSums:
        eastSums[ttl] = []
      eastSums[ttl].append([x,z])
    elif d == 'N':
        if ttl not in northSums:
          northSums[ttl] = []
        northSums[ttl].append([x,z])
  negs = 0
  for key in northSums:
    if key in eastSums:
      norths = northSums[key]
      easts = eastSums[key]
      for north in norths:
        for east in easts:
          if north[0] > east[0] and north[0] - east[0] <= k-1:
            negs += 1
  final = n*k-negs
  print(final)
