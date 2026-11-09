from collections import deque

t = int(input())
for _ in range(t):
  n,m,k = map(int,input().split())
  p = list(map(int,input().split()))
  toDo = deque()
  depths = {}
  for x in range(m):
    depths[x] = 0
  children = [[] for _ in range(n)]
  for x in range(n):
    val = p[x]
    if val != 0:
      children[val-1].append(x+1)
  for x in range(n):
    if p[x] == 0:
      toDo.append([x+1,0])
  while len(toDo) != 0:
    val = toDo.pop()
    if val[1] >= m:
      break
    depths[val[1]] += 1
    for child in children[val[0]-1]:
      toDo.appendleft([child,val[1]+1])

  residue = 0
  cnt = 0
  for semester in range(m):
    current = depths[semester]
    #entirely by residue
    if residue >= k:
      residue -= k
      cnt += k
      residue += current
    #partially by residue and then fully by semester
    elif (current+residue) >= k:
      current -= (k-residue)
      residue = 0
      cnt += k
      residue = current
    else:
      cnt += current + residue
      residue = 0 
  print(cnt)


