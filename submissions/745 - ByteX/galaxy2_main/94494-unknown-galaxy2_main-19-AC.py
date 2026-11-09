import sys
from array import array


def solve():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    T = int(next(it))
    out_lines = []
    INF = 1_500_000_000

    for _ in range(T):
        N = int(next(it))
        M = int(next(it))
        Q = int(next(it))
        grid = [next(it) for _ in range(N)]

        W = 2 * N
        S_total = M * W
        valid = bytearray(S_total)

        # mode 0 = blue, mode 1 = red
        for c in range(M):
            base = c * W
            for r in range(N):
                ch = grid[r][c]
                if ch == 46 or ch == 66:      # '.' or 'B'
                    valid[base + r] = 1       # blue
                if ch == 46 or ch == 82:      # '.' or 'R'
                    valid[base + N + r] = 1   # red

        adj = [[] for _ in range(S_total)]

        for c in range(M):
            base = c * W
            for r in range(N):
                ch = grid[r][c]
                for mode in (0, 1):
                    u = base + mode * N + r
                    if not valid[u]:
                        continue

                    if r > 0:
                        v = base + mode * N + (r - 1)
                        if valid[v]:
                            adj[u].append(v)
                    if r + 1 < N:
                        v = base + mode * N + (r + 1)
                        if valid[v]:
                            adj[u].append(v)

                    if c > 0:
                        v = (c - 1) * W + mode * N + r
                        if valid[v]:
                            adj[u].append(v)
                    if c + 1 < M:
                        v = (c + 1) * W + mode * N + r
                        if valid[v]:
                            adj[u].append(v)

                    if ch == 46:  # '.' allows spin
                        v = base + (1 - mode) * N + r
                        if valid[v]:
                            adj[u].append(v)

        col_of = [0] * S_total
        rem_of = [0] * S_total
        for i in range(S_total):
            col_of[i] = i // W
            rem_of[i] = i % W

        visited = [0] * S_total
        dist = [0] * S_total
        q = [0] * S_total
        stamp = 0

        node_l = []
        node_r = []
        node_mid = []
        node_arr = []
        node_left = []
        node_right = []

        def build_node(l, r):
            nonlocal stamp
            mid = (l + r) // 2
            L = r - l + 1
            V = W * L
            arr = array('i', [INF]) * (W * V)

            for s in range(W):
                start = mid * W + s
                if not valid[start]:
                    continue

                stamp += 1
                visited[start] = stamp
                dist[start] = 0

                offset = s * V
                local = (mid - l) * W + s
                arr[offset + local] = 0

                q[0] = start
                head = 0
                tail = 1

                while head < tail:
                    u = q[head]
                    head += 1
                    du = dist[u] + 1

                    for v in adj[u]:
                        cv = col_of[v]
                        if cv < l or cv > r:
                            continue
                        if visited[v] == stamp:
                            continue

                        visited[v] = stamp
                        dist[v] = du
                        local_v = (cv - l) * W + rem_of[v]
                        arr[offset + local_v] = du

                        q[tail] = v
                        tail += 1

            idx = len(node_l)
            node_l.append(l)
            node_r.append(r)
            node_mid.append(mid)
            node_arr.append(arr)
            node_left.append(-1)
            node_right.append(-1)

            if l <= mid - 1:
                node_left[idx] = build_node(l, mid - 1)
            if mid + 1 <= r:
                node_right[idx] = build_node(mid + 1, r)

            return idx

        root = build_node(0, M - 1) if M > 0 else -1

        for _q in range(Q):
            Rstart = int(next(it))
            Cstart = int(next(it))
            Rend = int(next(it))
            Cend = int(next(it))
            K = int(next(it))

            start = Cstart * W + Rstart  # blue mode, rem = row
            end_blue = Cend * W + Rend
            end_red = Cend * W + N + Rend

            ans = INF
            node = root
            cu = Cstart
            c_end = Cend

            while node != -1:
                l = node_l[node]
                r = node_r[node]
                mid = node_mid[node]
                arr = node_arr[node]

                V = W * (r - l + 1)

                lu = (cu - l) * W + Rstart
                l1 = (c_end - l) * W + Rend
                l2 = (c_end - l) * W + N + Rend

                best = INF
                idx_u = lu
                idx1 = l1
                idx2 = l2

                for _s in range(W):
                    d1 = arr[idx_u]
                    if d1 < INF:
                        d2 = arr[idx1]
                        if d2 < INF:
                            val = d1 + d2
                            if val < best:
                                best = val

                        d3 = arr[idx2]
                        if d3 < INF:
                            val = d1 + d3
                            if val < best:
                                best = val

                    idx_u += V
                    idx1 += V
                    idx2 += V

                if best < ans:
                    ans = best

                if cu < mid and c_end < mid:
                    node = node_left[node]
                elif cu > mid and c_end > mid:
                    node = node_right[node]
                else:
                    break

            out_lines.append("YES" if ans <= K else "NO")

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()