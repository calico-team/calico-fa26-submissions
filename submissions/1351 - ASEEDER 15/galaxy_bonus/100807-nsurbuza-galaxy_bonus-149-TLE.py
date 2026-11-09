t = int(input())

def dfs(graph, dest_x, dest_y, row, col):
    stack = []
    visited = set()

    # B - 0
    # R - 1

    if graph[dest_x][dest_y] == '.':
        stack.append((dest_x, dest_y, 0))
        stack.append((dest_x, dest_y, 1))
        visited.add((dest_x, dest_y, 0))
        visited.add((dest_x, dest_y, 1))
    elif graph[dest_x][dest_y] == 'R':
        stack.append((dest_x, dest_y, 1))
        visited.add((dest_x, dest_y, 1))
    elif graph[dest_x][dest_y] == 'B':
        stack.append((dest_x, dest_y, 0))
        visited.add((dest_x, dest_y, 0))

    direction = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    while stack:
        curr_x, curr_y, curr_mode = stack.pop()
        for dx, dy in direction:
            new_x, new_y = curr_x + dx, curr_y + dy
            if 0 <= new_x < row and 0 <= new_y < col:
                if (new_x, new_y, curr_mode) not in visited:
                    if graph[new_x][new_y] == ".":
                        stack.append((new_x, new_y, 1))
                        stack.append((new_x, new_y, 0))

                        visited.add((new_x, new_y, 1))
                        visited.add((new_x, new_y, 0))

                    if curr_mode == 0 and graph[new_x][new_y] == "R" or curr_mode == 1 and graph[new_x][new_y] == "B":
                        continue

                    stack.append((new_x, new_y, curr_mode))
                    visited.add((new_x, new_y, curr_mode))

    return visited

for i in range(t):
    n, q, r = map(int, input().split())

    graph = []
    for z in range(n):
        graph.append(list(input()))

    query = []
    for z in range(r):
        start_x, start_y, end_x, end_y = map(int, input().split())
        query.append((start_x, start_y, end_x, end_y))


    # print(all_reachable)
    # print(query)
    for start_x, start_y, _1, _2 in query:
        all_reachable = dfs(graph, _1, _2, n, q)
        if (start_x, start_y, 0) in all_reachable:
            print("YES")
        elif (start_x, start_y, 1) in all_reachable:
            print("YES")
        else:
            print("NO")