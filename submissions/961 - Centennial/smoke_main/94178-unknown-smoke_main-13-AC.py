t = int(input())
for _ in range(t):
    nr, seconds = map(int, input().split())
    requests = list(map(int, input().split()))

    p = []
    ok = True

    for req in requests:
        rec = 0
        while len(p) > 0 and p[0] <= req:
            p.pop(0)
            rec += 1

        if len(p) == 2:
            ok = False
            break

        if rec > 0 or not p:
            p.append(req + seconds)
        else:
            p.append(max(req, p[0]) + seconds)

        p.sort()

    print("YES" if ok else "NO")