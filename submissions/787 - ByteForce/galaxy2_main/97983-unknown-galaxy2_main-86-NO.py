from collections import deque
from array import array


def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]],
          K: list[int]) -> list[str]:

    INF = 10**9
    nodes = []

    def is_active(r, c, mode):
        if G[r][c] == '.':
            return True
        if G[r][c] == 'B':
            return mode == 0
        return mode == 1

    def build(left, right):
        if left > right:
            return -1

        mid = (left + right) // 2
        node_id = len(nodes)

        nodes.append(None)

        width = right - left + 1
        size = width * N * 2

        separators = []

        for r in range(N):
            for mode in range(2):
                if is_active(r, mid, mode):
                    separators.append((r, mode))

        all_distances = []

        for sr, smode in separators:
            dist = array('i', [-1]) * size

            def get_id(r, c, mode):
                return ((c - left) * N + r) * 2 + mode

            start_id = get_id(sr, mid, smode)
            dist[start_id] = 0

            queue = deque()
            queue.append((sr, mid, smode))

            while queue:
                r, c, mode = queue.popleft()
                current_id = get_id(r, c, mode)
                current_dist = dist[current_id]

                nr = r - 1
                nc = c
                if nr >= 0 and is_active(nr, nc, mode):
                    nxt = get_id(nr, nc, mode)
                    if dist[nxt] == -1:
                        dist[nxt] = current_dist + 1
                        queue.append((nr, nc, mode))

                nr = r + 1
                if nr < N and is_active(nr, nc, mode):
                    nxt = get_id(nr, nc, mode)
                    if dist[nxt] == -1:
                        dist[nxt] = current_dist + 1
                        queue.append((nr, nc, mode))

                nr = r
                nc = c - 1
                if nc >= left and is_active(nr, nc, mode):
                    nxt = get_id(nr, nc, mode)
                    if dist[nxt] == -1:
                        dist[nxt] = current_dist + 1
                        queue.append((nr, nc, mode))

                nc = c + 1
                if nc <= right and is_active(nr, nc, mode):
                    nxt = get_id(nr, nc, mode)
                    if dist[nxt] == -1:
                        dist[nxt] = current_dist + 1
                        queue.append((nr, nc, mode))

                if G[r][c] == '.':
                    new_mode = 1 - mode
                    nxt = get_id(r, c, new_mode)

                    if dist[nxt] == -1:
                        dist[nxt] = current_dist + 1
                        queue.append((r, c, new_mode))

            all_distances.append(dist)

        left_child = build(left, mid - 1)
        right_child = build(mid + 1, right)

        nodes[node_id] = (
            left, right, mid,
            separators, all_distances,
            left_child, right_child
        )

        return node_id

    root = build(0, M - 1)

    def shortest_distance(sr, sc, er, ec):
        best = INF
        node_id = root

        while node_id != -1:
            left, right, mid, separators, distances, lc, rc = nodes[node_id]

            width_id_start_blue = ((sc - left) * N + sr) * 2
            width_id_end_blue = ((ec - left) * N + er) * 2
            width_id_end_red = width_id_end_blue + 1

            for dist in distances:
                d1 = dist[width_id_start_blue]

                if d1 == -1:
                    continue

                d2 = dist[width_id_end_blue]
                if d2 != -1:
                    best = min(best, d1 + d2)

                d2 = dist[width_id_end_red]
                if d2 != -1:
                    best = min(best, d1 + d2)


            if sc < mid and ec < mid:
                node_id = lc
            elif sc > mid and ec > mid:
                node_id = rc
            else:
                break

        return best

    answers = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]

        distance = shortest_distance(sr, sc, er, ec)

        if distance <= K[i]:
            answers.append("YES")
        else:
            answers.append("NO")

    return answers
