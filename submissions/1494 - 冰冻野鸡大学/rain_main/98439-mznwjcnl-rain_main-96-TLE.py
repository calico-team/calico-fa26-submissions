t = int(input())
for i in range(t):
  n, k = [int(i) for i in input().split()]
  drones = []
  dirs = []
  for i in range(n):
    x = input().split()
    drones.append([int(i) for i in x[:-1]])
    dirs.append(x[-1])
  overlap = 0
  for i in range(n):
    for j in range(i + 1, n):
      if dirs[i] != dirs[j]:
        x = drones[i][0] - drones[j][0]
        y = drones[j][1] - drones[i][1]
        if x == y and abs(x) < k and (x < 0 and dirs[i] == 'E' or x > 0 and dirs[i] == 'N'):
          overlap += 1
  print(n * k - overlap)
