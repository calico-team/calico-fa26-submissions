import sys


def build_graph(grid, n, m):
    graph = [[] for _ in range(2 * n * m)]

    for c in range(m):
        for r in range(n):
            cell = 2 * (c * n + r)
            title = grid[r][c]

            if title == ".":
                graph[cell].append(cell + 1)
                graph[cell + 1].append(cell)

            for nr, nc in ((r - 1, c), (r, c-1)):
                if nr < 0 or nc < 0:
                   continue

                other = 2 * (nr * n + nr)
                for mode, color in enumerate("BR"):
                    if title in (".", color) and grid[nr][nc] in (".", color):
                        graph[cell + mode].append(other + mode)
                        graph[other + mode].append(cell + mode)

    return graph

def get_components(graph):
    component = [-1] * len(graph)
    sizes = []

    for start in range(len(graph)):
        if component[start] != -1:
            continue

        number = len(sizes)
        component[start] = number
        queue = [start]

        for u in queue:
            for v in graph[u]:
                if component[v] == -1:
                    component[v] = number
                    queue.append(v)

        sizes.append(len(queue))

    return component, sizes

def answer_queries(grid, n, m, queries):
    graph = build_graph(grid, n, m)
    component, sizes = get_components(graph)
    answer = ["NO"] * len(queries)
    pending = []

    for index, (sr, sc, tr, tc, k) in enumerate(queries):
        if abs(sr - tr) + abs(sc - tc) > k:
            continue

        start = 2* (sc * n + sr)
        end = 2* (tc * n + tr)
        title = grid[tr][tc]

        first_mode = 1 if title == "R" else 0
        second_mode = 0 if title == "B" else 1
        first = end + first_mode
        second = end + second_mode

        if component[start] != component[first]:
            continue

        if start == first or k >= sizes[component[start]] - 1:
            answer[index] = "YES"
            continue

        parity = (sr + sc + tr + tc) % 2
        limit_first = k - (k + parity + first_mode) % 2
        limit_second = k - (k + parity + second_mode) % 2

        pending.append(
            (start, first, second, limit_first, limit_second, index)
        )

    distance = [-2] * len(graph)
    tasks = [(0, m - 1, pending)]

    while tasks:
        left, right, pending = tasks.pop()
        if not pending:
            continue

        middle = (left + right) // 2
        low = 2 * n * left
        high = 2 * n * (right + 1)
        middle_low = 2 * n * middle
        middle_high = middle_low + 2 * n
        cutoff = max(max(query[3], query[4]) for query in pending)

        for row in range(n):
            distance[low:high] = [-1] * (high - low)
            cell = middle_low + 2 * row
            title = grid[row][middle]
            queue = []

            if title != "R":
                distance[cell] = 0
                queue.append(cell)

            if title !="B":
                distance[cell + 1] = 0