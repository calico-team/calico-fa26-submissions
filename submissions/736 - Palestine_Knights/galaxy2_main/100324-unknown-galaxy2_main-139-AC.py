from collections import deque
from array import array

def solve(N, M, Q, G, start, end, K):
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    K: the maximum number of seconds allowed for each query
    """

    H = 2 * N
    nodes = []

    # Each cell has two states:
    # even = blue, odd = red
    def active(r, c, mode):
        tile = G[r][c]
        return tile == '.' or (
            mode == 0 and tile == 'B'
        ) or (
            mode == 1 and tile == 'R'
        )

    def build(left, right):
        mid = (left + right) // 2
        width = right - left + 1
        count = width * H

        node_id = len(nodes)
        nodes.append(None)

        distances = []

        # BFS from every active state in middle column
        for r in range(N):
            for mode in range(2):
                if not active(r, mid, mode):
                    continue

                dist = array('i', [-1]) * count
                source = (mid - left) * H + 2 * r + mode

                dist[source] = 0
                queue = deque([source])

                while queue:
                    state = queue.popleft()
                    d = dist[state] + 1

                    column, rem = divmod(state, H)
                    row, current_mode = divmod(rem, 2)
                    col = left + column

                    # Spin on normal tiles
                    if G[row][col] == '.':
                        other = state ^ 1
                        if dist[other] == -1:
                            dist[other] = d
                            queue.append(other)

                    # Up
                    if row > 0 and active(row - 1, col, current_mode):
                        nxt = state - 2
                        if dist[nxt] == -1:
                            dist[nxt] = d
                            queue.append(nxt)

                    # Down
                    if row + 1 < N and active(row + 1, col, current_mode):
                        nxt = state + 2
                        if dist[nxt] == -1:
                            dist[nxt] = d
                            queue.append(nxt)

                    # Left
                    if col > left and active(row, col - 1, current_mode):
                        nxt = state - H
                        if dist[nxt] == -1:
                            dist[nxt] = d
                            queue.append(nxt)

                    # Right
                    if col < right and active(row, col + 1, current_mode):
                        nxt = state + H
                        if dist[nxt] == -1:
                            dist[nxt] = d
                            queue.append(nxt)

                distances.append(dist)

        nodes[node_id] = (
            left, right, mid, distances, -1, -1
        )

        left_child = -1
        right_child = -1

        if left < mid:
            left_child = build(left, mid - 1)

        if mid < right:
            right_child = build(mid + 1, right)

        nodes[node_id] = (
            left, right, mid, distances,
            left_child, right_child
        )

        return node_id

    root = build(0, M - 1)

    results = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        limit = K[i]

        if (sr, sc) == (er, ec):
            results.append("YES")
            continue

        best = limit + 1
        node_id = root

        while node_id != -1:
            left, right, mid, distances, lc, rc = nodes[node_id]

            source = (sc - left) * H + 2 * sr
            target_blue = (ec - left) * H + 2 * er
            target_red = target_blue + 1

            for dist in distances:
                a = dist[source]

                if a == -1 or a >= best:
                    continue

                b = dist[target_blue]
                if b != -1 and a + b < best:
                    best = a + b

                b = dist[target_red]
                if b != -1 and a + b < best:
                    best = a + b

            if best <= limit:
                break

            if sc < mid and ec < mid:
                node_id = lc
            elif sc > mid and ec > mid:
                node_id = rc
            else:
                break

        results.append("YES" if best <= limit else "NO")

    return results

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()
