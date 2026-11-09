t = int(input())

for _ in range(t):
    n, m, k = map(int, input().split())
    p = [0] + list(map(int, input().split()))

    depth = [0] * (n + 1)
    cnt = [0] * (n + 1)

    for c in range(1, n + 1):
        path = []

        while c != 0 and depth[c] == 0:
            path.append(c)
            c = p[c]

        while path:
            c = path.pop()
            depth[c] = depth[p[c]] + 1
            cnt[depth[c]] += 1

    avail = 0
    ans = 0

    for s in range(1, min(m, n) + 1):
        avail += cnt[s]
        take = min(k, avail)
        ans += take
        avail -= take

    print(ans)