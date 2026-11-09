t = int(input())
for _ in range(t):
  n,m,k = map(int,input().split())
  p = list(map(int,input().split()))
  toDo = []
  depths = []
  for x in range(n):
    if p[x] == 0:
      toDo.append([x+1,0])
  while toDo != []:
    val = toDo.pop()
    depths.append(val[1])
    for x in range(n):
      if p[x] == val[0]:
        toDo.append([x+1,val[1]+1])

  residue = 0
  cnt = 0
  for semester in range(m):
    current = depths.count(semester)
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


