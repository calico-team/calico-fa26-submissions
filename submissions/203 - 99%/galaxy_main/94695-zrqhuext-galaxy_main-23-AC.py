t = int(input())

for _ in range(t):
    n, m, q = map(int, input().split())

    grid = []
    for row in range(n):
        grid.append(input().strip())

    groups = []
    for row in range(n):
        groups.append([-1] * m)

    id = 0
    dir = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    for row in range(n):
        for col in range(m):
            if groups[row][col] != -1:
                continue

            groups[row][col] = id
            stack = [(row, col)]
            # print(stack)

            while stack:
                r, c = stack.pop()

                for dr, dc in dir:
                    new_row = r + dr
                    new_col = c + dc

                    if new_row < 0 or new_row >= n:
                        continue
                    if new_col < 0 or new_col >= m:
                        continue
                    if groups[new_row][new_col] != -1:
                        continue

                    current_tile = grid[r][c]
                    next_tile = grid[new_row][new_col]

                    if current_tile == next_tile or current_tile == "." or next_tile == ".":
                        groups[new_row][new_col] = id
                        stack.append((new_row, new_col))

            id += 1

    for _ in range(q):
        sr, sc, er, ec = map(int, input().split())

        if groups[sr][sc] == groups[er][ec]:
            print("YES")
        else:
            print("NO")