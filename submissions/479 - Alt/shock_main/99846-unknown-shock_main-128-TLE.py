import sys
from math import isqrt

def solve():
    input_data = sys.stdin.buffer.read().split()
    if not input_data:
        return

    ptr = 0
    num_tests = int(input_data[ptr])
    ptr += 1

    out = []

    for _ in range(num_tests):
        R = int(input_data[ptr])
        C = int(input_data[ptr + 1])
        Q = int(input_data[ptr + 2])
        ptr += 3

        quakes = list(map(int, input_data[ptr : ptr + 3 * Q]))
        ptr += 3 * Q

        grid = [0] * (R * C)
        intervals = [[] for _ in range(R)]
        nxt = list(range(R + 1))
        active_rows = R

        for i in range(3 * (Q - 1), -1, -3):
            if not active_rows:
                break

            qr, qc, p = quakes[i], quakes[i + 1], quakes[i + 2]
            p2 = p * p

            r_min = max(0, qr - p)
            r_max = min(R - 1, qr + p)

            r = r_min
            while r <= r_max:
                root = r
                while nxt[root] != root:
                    root = nxt[root]
                curr = r
                while nxt[curr] != root:
                    nxt[curr], curr = root, nxt[curr]
                r = root
                if r > r_max:
                    break

                dr2 = (r - qr) ** 2
                dc_max = isqrt(p2 - dr2)
                c_min = max(0, qc - dc_max)
                c_max = min(C - 1, qc + dc_max)

                if c_min <= c_max:
                    row_ints = intervals[r]
                    n_ints = len(row_ints)
                    if n_ints == 1 and row_ints[0][0] <= c_min and row_ints[0][1] >= c_max:
                        r += 1
                        continue

                    r_idx = r * C
                    base = p2 - dr2 + 1

                    lo, hi = 0, n_ints
                    target = c_min - 1
                    while lo < hi:
                        mid = (lo + hi) >> 1
                        if row_ints[mid][1] < target:
                            lo = mid + 1
                        else:
                            hi = mid
                    first = lo

                    c, idx = c_min, first
                    while c <= c_max:
                        if idx < n_ints and row_ints[idx][0] <= c:
                            if row_ints[idx][1] >= c:
                                c = row_ints[idx][1] + 1
                            idx += 1
                            continue
                        
                        g_end = row_ints[idx][0] - 1 if (idx < n_ints and row_ints[idx][0] <= c_max) else c_max
                        s = r_idx + c
                        grid[s : s + g_end - c + 1] = [
                            base - (x * x) for x in range(c - qc, g_end - qc + 1)
                        ]
                        c = g_end + 1

                    while idx < n_ints and row_ints[idx][0] <= c_max + 1:
                        idx += 1
                    
                    m_lo, m_hi = c_min, c_max
                    if idx > first:
                        if row_ints[first][0] < m_lo: m_lo = row_ints[first][0]
                        if row_ints[idx - 1][1] > m_hi: m_hi = row_ints[idx - 1][1]
                    row_ints[first:idx] = [[m_lo, m_hi]]

                    if m_lo == 0 and m_hi == C - 1:
                        nxt[r] = r + 1
                        active_rows -= 1

                r += 1

        for r in range(R):
            s = r * C
            out.append(" ".join(map(str, grid[s : s + C])))

    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    solve()
