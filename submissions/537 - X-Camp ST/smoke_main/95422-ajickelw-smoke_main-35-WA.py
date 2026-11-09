t = int(input())

for i in range(t):
  n, r = map(int, input().split())
  have = 2
  times = list(map(int, input().split()))
  can = True

  i = 0
  time = 0

  while i < n:

    if r > times[0]:
      print('NO')
      can = False
      break

    time += r
    if have == 2:
      have += 0
    elif have < 2:
      have += 1

    if time >= times[i]:
      if have <= 0:
        print('NO')
        can = False
        break
      else:
        have -= 1
        time = 0
        i += 1

  if can:
    print('YES')