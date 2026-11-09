t = int(input())
for T in range(t):
    s = input().split()
    n = int(s[0])
    k = int(s[1])
    l = []
    for i in range(n):
        s = input().split()
        a = []
        for j in range(3): a.append(int(s[j]))
        if s[3] == "E": a.append(0)
        else: a.append(1)
        l.append(a)

    r = 0
    for i in range(k):
        c = []
        for j in range(n):
            if not [l[j][0], l[j][1]] in c:
                c.append([l[j][0], l[j][1]])
                r += 1

        for j in range(n):
            d = l[j][3]
            l[j][d] += 1

    print(r)






