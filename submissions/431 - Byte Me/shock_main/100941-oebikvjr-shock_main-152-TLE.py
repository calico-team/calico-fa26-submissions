def find(parent, x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


T = int(input())

for _ in range(T):
    N, M, Q = map(int, input().split())
    earthquakes = []

    for _ in range(Q):
        R, C, P = map(int, input().split())
        earthquakes.append((R, C, P))

    grid = [[0] * M for _ in range(N)]
    parent = list(range(N * M + 1))

    for R, C, P in reversed(earthquakes):
        power = P * P

        for r in range(R - P, R + P + 1):
            vertical = (r - R) ** 2
            width = int((power - vertical) ** 0.5)
            left = r * M + C - width
            right = r * M + C + width

            x = find(parent, left)
            while x <= right:
                c = x % M
                grid[r][c] = power - vertical - (c - C) ** 2 + 1
                parent[x] = find(parent, x + 1)
                x = find(parent, x)

    for row in grid:
        print(*row)
