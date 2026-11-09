import bisect
t = int(input())
for i in range(t):
  n, k = [int(i) for i in input().split()]
  drones = []
  dirs = []
  for i in range(n):
    x = input().split()
    drones.append([int(i) for i in x[:-1]])
    dirs.append(x[-1])
  j = 0
  north = {}
  for i in range(n):
    if dirs[i] == 'N':
      north.setdefault(drones[i][0] + drones[i][1], []).append(drones[i][0])
  for v in north.values():
    v.sort()
  for i in range(n):
    if dirs[i] == 'E':
      a = drones[i][0]
      v = north.get(a + drones[i][1], [])
      j += bisect.bisect_left(v, a + k) - bisect.bisect_right(v, a)
  print(n * k - j)