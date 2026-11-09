T = int(input())

for _ in range(T):
    N, M, Q = map(int, input().split())

    grid = [[0] * M for _ in range(N)]

    earthquakes = []
    for _ in range(Q):
        R, C, P = map(int, input().split())
        earthquakes.append((R, C, P))

    # Process earthquakes in chronological order
    for R, C, P in earthquakes:
        for r in range(R - P, R + P + 1):
            for c in range(C - P, C + P + 1):

                distance_squared = (r - R) ** 2 + (c - C) ** 2

                if distance_squared <= P ** 2:
                    shock = P ** 2 - distance_squared + 1
                    grid[r][c] = shock

    # Print the final grid
    for row in grid:
        print(*row)
