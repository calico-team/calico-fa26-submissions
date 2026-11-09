from collections import deque

T = int(input())

for _ in range(T):
    N, M, Q = list(map(int, input().split()))

    grid = []
    for _ in range(N):
        grid.append(list(input()))

    possible = {(x, y): set() for y in range(M) for x in range(N)}

    visited = set()

    for x in range(N):
        for y in range(M):
            if (x, y) not in visited:
                visited.add((x, y))

                chain = set() 
                chain.add((x, y))

                to_visit = deque()
                to_visit.append((x, y))

                while len(to_visit) > 0:
                    curr = to_visit.popleft()
                    curr_x = curr[0]
                    curr_y = curr[1]
                    points = [(curr_x + 1, curr_y), (curr_x - 1, curr_y), (curr_x, curr_y + 1), (curr_x, curr_y - 1)]

                    for point in points:
                        if 0 <= point[0] < N and 0 <= point[1] < M:
                            if grid[curr[0]][curr[1]] == "." and point not in visited:
                                visited.add(point)
                                chain.add(point)
                                to_visit.append(point)
                            else:
                                if grid[point[0]][point[1]] == "." or grid[point[0]][point[1]] == grid[curr[0]][curr[1]]:
                                    if point not in visited:
                                        visited.add(point)
                                        chain.add(point)
                                        to_visit.append(point)

                for p in chain:
                    possible[p] = chain


    for _ in range(Q):
        R_start, C_start, R_end, C_end = list(map(int, input().split()))

        if (R_end, C_end) in possible[(R_start, C_start)]:
            print("YES")
        else:
            print("NO")