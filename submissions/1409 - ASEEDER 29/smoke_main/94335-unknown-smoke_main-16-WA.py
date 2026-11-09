t = int(input())
for T in range(t):
    s = input().split()
    n = int(s[0])
    r = int(s[1])
    c = 2
    ans = True
    a =[]
    s = input().split()
    for i in range(n): a.append(int(s[i]))

    for i in range(n):
        if i > 0:
            time = a[i] - a[i-1]
            if time >= r: c += 1
        c -= 1
        if c < 0:
            ans = False
            break

    if ans: print("YES")
    else: print("NO")
