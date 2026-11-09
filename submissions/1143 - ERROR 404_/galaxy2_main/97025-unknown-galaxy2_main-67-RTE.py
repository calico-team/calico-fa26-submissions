import sys
import numpy as np
from collections import deque

try:
    from numba import njit
    HAS_NUMBA = True
except Exception:
    HAS_NUMBA = False

if HAS_NUMBA:
    @njit
    def bfs_all_nb(grid, N, M, sr, sc, sm):
        total = 2 * N * M
        dist = np.empty(total, dtype=np.int64)
        for i in range(total):
            dist[i] = -1
        q = np.empty(total, dtype=np.int64)
        qh = 0
        qt = 0
        def idx(r, c, mode):
            return (mode * N + r) * M + c
        def active(r, c, mode):
            ch = grid[r, c]
            if ch == 0:
                return True
            if mode == 0:
                return ch == 2
            return ch == 1
        s = idx(sr, sc, sm)
        dist[s] = 0
        q[qt] = s
        qt += 1
        while qh < qt:
            cur = q[qh]
            qh += 1
            d = dist[cur]
            mode = cur // (N * M)
            rem = cur % (N * M)
            r = rem // M
            c = rem % M
            # spin
            if grid[r, c] == 0:
                nm = 1 - mode
                nid = idx(r, c, nm)
                if dist[nid] == -1:
                    dist[nid] = d + 1
                    q[qt] = nid
                    qt += 1
            # 4 neighbours
            if r > 0:
                nr = r - 1; nc = c
                if active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid
                        qt += 1
            if r + 1 < N:
                nr = r + 1; nc = c
                if active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid
                        qt += 1
            if c > 0:
                nr = r; nc = c - 1
                if active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid
                        qt += 1
            if c + 1 < M:
                nr = r; nc = c + 1
                if active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid
                        qt += 1
        return dist

    @njit
    def bfs_restricted_nb(grid, N, M, sr, sc, sm, tr, tc, tmodes, c_low, c_high):
        # tmodes : array of allowed modes for dest, length 2 with -1 padding
        total = 2 * N * M
        dist = np.empty(total, dtype=np.int64)
        for i in range(total):
            dist[i] = -1
        q = np.empty(total, dtype=np.int64)
        qh = 0; qt = 0
        def idx(r, c, mode):
            return (mode * N + r) * M + c
        def active(r, c, mode):
            ch = grid[r, c]
            if ch == 0:
                return True
            if mode == 0:
                return ch == 2
            return ch == 1
        s = idx(sr, sc, sm)
        dist[s] = 0
        q[qt] = s; qt += 1
        best = -1
        while qh < qt:
            cur = q[qh]; qh += 1
            d = dist[cur]
            if best != -1 and d >= best:
                # still need to continue? BFS order ensures first found is minimal
                # we can break if d > best
                if d > best:
                    break
            mode = cur // (N * M)
            rem = cur % (N * M)
            r = rem // M; c = rem % M
            if r == tr and c == tc:
                for k in range(2):
                    if tmodes[k] == mode:
                        if best == -1 or d < best:
                            best = d
            if best != -1 and d >= best:
                continue
            if grid[r, c] == 0:
                nm = 1 - mode
                nid = idx(r, c, nm)
                if dist[nid] == -1:
                    dist[nid] = d + 1
                    q[qt] = nid; qt += 1
            if r > 0:
                nr = r - 1; nc = c
                if nc >= c_low and nc <= c_high and active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid; qt += 1
            if r + 1 < N:
                nr = r + 1; nc = c
                if nc >= c_low and nc <= c_high and active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid; qt += 1
            if c > 0:
                nr = r; nc = c - 1
                if nc >= c_low and nc <= c_high and active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid; qt += 1
            if c + 1 < M:
                nr = r; nc = c + 1
                if nc >= c_low and nc <= c_high and active(nr, nc, mode):
                    nid = idx(nr, nc, mode)
                    if dist[nid] == -1:
                        dist[nid] = d + 1
                        q[qt] = nid; qt += 1
        return best

def bfs_all_py(grid_list, N, M, sr, sc, sm):
    # grid_list: list of strings
    def active(r, c, mode):
        ch = grid_list[r]