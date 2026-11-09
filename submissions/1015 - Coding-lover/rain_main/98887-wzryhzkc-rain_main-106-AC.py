t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    d = {}
    i = 0
    while i < n:
        p = input().split()
        x = int(p[0])
        y = int(p[1])
        dr = p[3]
        s = x + y
        if s not in d:
            d[s] = [[], []]
        if dr == "E":
            d[s][0].append(x)
        else:
            d[s][1].append(x)
        i = i + 1
    blocked = 0
    for e, nn in d.values():
        if not e or not nn:
            continue
        e.sort()
        nn.sort()
        l = 0
        r = 0
        for xn in nn:
            while r < len(e) and e[r] <= xn:
                r = r + 1
            while l < len(e) and e[l] <= xn - k:
                l = l + 1
            blocked = blocked + (r - l)
    print(n * k - blocked)
