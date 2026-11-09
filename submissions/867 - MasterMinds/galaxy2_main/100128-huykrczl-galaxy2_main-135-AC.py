
import sys
from array import array

def solve():
    input = sys.stdin.readline

    for _ in range(int(input())):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        mask = []
        for row in grid:
            for ch in row:
                mask.append(3 if ch == '.' else 1 if ch == 'B' else 2)

     
        nodes = []

        def build(l, r):
            mid = (l + r) // 2

            boundary = []
            for row in range(n):
                for mode in range(2):
                    if mask[row * m + mid] & (1 << mode):
                        boundary.append(((mid - l) * n + row) * 2 + mode)

            b = len(boundary)
            width = r - l + 1

            dist = array('i', [-1]) * (width * n * 2 * b)

            for j, start in enumerate(boundary):
                queue = [start]
                head = 0
                dist[start * b + j] = 0

                while head < len(queue):
                    u = queue[head]
                    head += 1

                    nd = dist[u * b + j] + 1

                    col = u // (2 * n)
                    rem = u % (2 * n)
                    row = rem // 2
                    mode = rem & 1

                    cell = row * m + l + col

                    if row > 0:
                        v = u - 2
                        if mask[cell - m] & (1 << mode) and dist[v * b + j] == -1:
                            dist[v * b + j] = nd
                            queue.append(v)

                    if row + 1 < n:
                        v = u + 2
                        if mask[cell + m] & (1 << mode) and dist[v * b + j] == -1:
                            dist[v * b + j] = nd
                            queue.append(v)

                    if col > 0:
                        v = u - 2 * n
                        if mask[cell - 1] & (1 << mode) and dist[v * b + j] == -1:
                            dist[v * b + j] = nd
                            queue.append(v)

                    if col + 1 < width:
                        v = u + 2 * n
                        if mask[cell + 1] & (1 << mode) and dist[v * b + j] == -1:
                            dist[v * b + j] = nd
                            queue.append(v)

                    if mask[cell] == 3:
                        v = u ^ 1
                        if dist[v * b + j] == -1:
                            dist[v * b + j] = nd
                            queue.append(v)

            pos = {v: i for i, v in enumerate(boundary)}

            idx = len(nodes)
            nodes.append([l, r, mid, b, dist, pos, -1, -1])

            if l < mid:
                nodes[idx][6] = build(l, mid - 1)

            if mid < r:
                nodes[idx][7] = build(mid + 1, r)

            return idx

        root = build(0, m - 1)

        answers = []

        for _ in range(q):
            sr, sc, er, ec, k = map(int, input().split())

            best = 10**18
            node = root

            while node != -1:
                l, r, mid, b, dist, pos, left, right = nodes[node]

                start = ((sc - l) * n + sr) * 2
                targets = [
                    ((ec - l) * n + er) * 2 + mode
                    for mode in range(2)
                    if mask[er * m + ec] & (1 << mode)
                ]

                if sc == mid:
                    j = pos[start]
                    for target in targets:
                        d = dist[target * b + j]
                        if d >= 0:
                            best = min(best, d)
                    break

                if ec == mid:
                    for target in targets:
                        j = pos[target]
                        d = dist[start * b + j]
                        if d >= 0:
                            best = min(best, d)
                    break

                for j in range(b):
                    ds = dist[start * b + j]

                    if ds < 0:
                        continue

                    dt = min(
                        (dist[target * b + j]
                         for target in targets
                         if dist[target * b + j] >= 0),
                        default=10**18
                    )

                    best = min(best, ds + dt)

                if sc < mid and ec < mid:
                    node = left
                elif sc > mid and ec > mid:
                    node = right
                else:
                    break

            answers.append("YES" if best <= k else "NO")

        print("\n".join(answers))


if __name__ == "__main__":
    solve()
