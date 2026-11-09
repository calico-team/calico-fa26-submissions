t = int(input())


def find(pos):
    while nxt[pos] != pos:
        nxt[pos] = nxt[nxt[pos]]
        pos = nxt[pos]
    return pos

for _ in range(t):
    n, m, q = map(int, input().split())

    quakes = []
    for _ in range(q):
        r, c, p = map(int, input().split())
        quakes.append((r, c, p))

    ans = [0] * (n * m)
    nxt = list(range(n * m + 1))

    for r, c, p in reversed(quakes):
        reach = 0

        for row in range(r - p, r + p + 1):
            remaining = p * p - (row - r) ** 2

            while (reach + 1) ** 2 <= remaining:
                reach += 1
            # print(reach)

            while reach * reach > remaining:
                reach -= 1
            # print("e", reach)

            pos = find(row * m + c - reach)
            end = row * m + c + reach

            while pos <= end:
                col = pos % m
                ans[pos] = remaining - (col - c) ** 2
                ans[pos] += 1

                nxt[pos] = find(pos + 1)
                pos = nxt[pos]

    for r in range(n):
        s = r * m
        l = s + m
        values = ans[s:l]
        print(*values)