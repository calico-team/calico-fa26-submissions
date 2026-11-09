t = int(input())
for i in range(t):
  n, k = [int(i) for i in input().split()]
  drones = []
  dirs = []
  for i in range(n):
    x = input().split()
    drones.append([int(i) for i in x[:-1]])
    dirs.append(x[-1])
  sum = 0
  for i in range(k):
    stuff = []
    for j in range(n):
      y = [drones[j][0], drones[j][1]]
      if y not in stuff:
        stuff.append(y)
    sum += len(stuff)
    for j in range(n):
      if dirs[j] == 'E':
        drones[j][0] += 1
      else:
        drones[j][1] += 1
  print(sum)
