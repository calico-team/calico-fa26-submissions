t = int(input())

def dfs(graph, row, col):
    connected_components = {}
    visited = set()

    # B - 0
    # R - 1

    new_id = 0
    for r in range(row):
        for c in range(col):

            color = 0
            if graph[r][c] == 'B':
                color = 0
            elif graph[r][c] == 'R':
                color = 1

            starting_coordinates = (r, c, color)

            if starting_coordinates in connected_components:
                continue

            new_id += 1
            connected_components[starting_coordinates] = new_id

            stack = [starting_coordinates]

            if graph[r][c] == ".":
                skibidi = (r, c, 1)
                connected_components[skibidi] = new_id
                stack.append(skibidi)

                visited.add(skibidi)

            visited.add(starting_coordinates)

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

                                if (new_x, new_y, 1) not in connected_components:
                                    connected_components[(new_x, new_y, 1)] = new_id
                                if (new_x, new_y, 0) not in connected_components:
                                    connected_components[(new_x, new_y, 0)] = new_id

                                visited.add((new_x, new_y, 1))
                                visited.add((new_x, new_y, 0))

                            if curr_mode == 0 and graph[new_x][new_y] == "R" or curr_mode == 1 and graph[new_x][new_y] == "B":
                                continue

                            if (new_x, new_y, curr_mode) not in connected_components:
                                stack.append((new_x, new_y, curr_mode))
                                connected_components[(new_x, new_y, curr_mode)] = new_id

                                visited.add((new_x, new_y, curr_mode))

    return connected_components

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