def solv(n,r,a):

    c1 = 0
    c2 = 0
    for i in range(n):
        if c1 < a[i]:
            c1 = a[i] + max(c2 - a[i], 0) + r
        elif c2 < a[i]:
            c2 = a[i] + max(c1 - a[i], 0) + r
        else:
            return "NO"
    return "YES"

pp = int(input())
l = []
for p in range(pp):
    n,r = [int(x) for x in input().split()]
    a = [int(x) for x in input().split()]
    l.append((n,r,a))

for i in l:
    n,r,a = i
    print(solv(n,r,a))