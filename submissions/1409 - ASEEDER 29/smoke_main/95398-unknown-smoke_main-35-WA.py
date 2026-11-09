t = int(input())
for T in range(t):
    s = input().split()
    n = int(s[0])
    r = int(s[1])
    c = [0, 0]
    ans = True
    a =[]
    s = input().split()
    for i in range(n):
        a.append(int(s[i]))

    for i in range(n):
        if i > 0:
            time = a[i] - a[i-1]
            if c[0] > 0:
                temp = c[0]
                c[0] -= time
                time -= temp
            if c[1] > 0 and time > 0:
                c[1] -= time

        if c[0] <= 0: c[0] = r
        elif c[1] <= 0: c[1] = r
        else:
            ans = False
            break

    if ans: print("YES")
    else: print("NO")
