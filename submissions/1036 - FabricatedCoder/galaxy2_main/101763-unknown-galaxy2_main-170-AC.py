import sys
from collections import deque

def solve():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    test_cases = int(next(it))
    output = []

    for _ in range(test_cases):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))
        grid = [next(it) for _ in range(n)]

        starts = [0] * q
        start_cols = [0] * q
        ends = [0] * q
        end_cols = [0] * q
        limits = [0] * q

        for i in range(q):
            rs = int(next(it))
            cs = int(next(it))
            re = int(next(it))
            ce = int(next(it))
            starts[i] = rs * m + cs
            start_cols[i] = cs
            ends[i] = re * m + ce
            end_cols[i] = ce
            limits[i] = int(next(it))

        states = 2 * n * m
        distances = [-1] * states
        answers = [10**18] * q

        def state(mode, row, col):
            return (mode * n + row) * m + col

        def active(mode, row, col):
            tile = grid[row][col]
            return tile == 46 or (mode == 0 and tile == 66) or (
                mode == 1 and tile == 82
            )

        def bfs(source, left, right):
            distances[source] = 0
            visited = [source]
            queue = deque([source])

            while queue:
                current = queue.popleft()
                col = current % m
                temp = current // m
                row = temp % n
                mode = temp // n
                distance = distances[current] + 1

                if col > left:
                    nxt = current - 1
                    if distances[nxt] < 0 and active(mode, row, col - 1):
                        distances[nxt] = distance
                        visited.append(nxt)
                        queue.append(nxt)
                if col < right:
                    nxt = current + 1
                    if distances[nxt] < 0 and active(mode, row, col + 1):
                        distances[nxt] = distance
                        visited.append(nxt)
                        queue.append(nxt)
                if row:
                    nxt = current - m
                    if distances[nxt] < 0 and active(mode, row - 1, col):
                        distances[nxt] = distance
                        visited.append(nxt)
                        queue.append(nxt)
                if row + 1 < n:
                    nxt = current + m
                    if distances[nxt] < 0 and active(mode, row + 1, col):
                        distances[nxt] = distance
                        visited.append(nxt)
                        queue.append(nxt)

                if grid[row][col] == 46:
                    nxt = current + n * m if mode == 0 else current - n * m
                    if distances[nxt] < 0:
                        distances[nxt] = distance
                        visited.append(nxt)
                        queue.append(nxt)

            return visited

        def process(left, right, query_ids):
            if not query_ids:
                return

            middle = (left + right) // 2
            sources = []
            for row in range(n):
                if active(0, row, middle):
                    sources.append(state(0, row, middle))
                if active(1, row, middle):
                    sources.append(state(1, row, middle))

            for source in sources:
                visited = bfs(source, left, right)
                for query_id in query_ids:
                    start_state = starts[query_id]
                    # Mode 0 is blue; the input start tile is always normal.
                    start_distance = distances[start_state]
                    if start_distance < 0:
                        continue

                    destination = ends[query_id]
                    end_distance = distances[destination]
                    other_distance = distances[destination + n * m]
                    if end_distance < 0 or (
                        0 <= other_distance < end_distance
                    ):
                        end_distance = other_distance
                    if end_distance >= 0:
                        candidate = start_distance + end_distance
                        if candidate < answers[query_id]:
                            answers[query_id] = candidate

                for item in visited:
                    distances[item] = -1

            if left == right:
                return

            left_queries = []
            right_queries = []
            for query_id in query_ids:
                if start_cols[query_id] <= middle and end_cols[query_id] <= middle:
                    left_queries.append(query_id)
                elif start_cols[query_id] > middle and end_cols[query_id] > middle:
                    right_queries.append(query_id)

            process(left, middle, left_queries)
            process(middle + 1, right, right_queries)

        process(0, m - 1, list(range(q)))

        for answer, limit in zip(answers, limits):
            output.append("YES" if answer <= limit else "NO")

    sys.stdout.write("\n".join(output))

if __name__ == "__main__":
    solve()
