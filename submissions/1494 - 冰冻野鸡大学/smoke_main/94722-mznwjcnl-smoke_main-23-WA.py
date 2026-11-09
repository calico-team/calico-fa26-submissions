t = int(input())
for i in range(t):
  n, r = [int(i) for i in input().split()]
  ls = [int(i) for i in input().split()]
  f = 0
  s = 0
  flag = True
  for i in range(ls[-1]):
    if i in ls:
      if f >= r:
        f = 0
      elif s >= r:
        s = 0
      else:
        print('NO')
        flag = False
        break
    f += 1
    s += 1
  if flag:
    print('YES')
