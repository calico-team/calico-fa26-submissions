from __future__ import annotations
from collections import deque

try:
    import numpy as np
    from scipy.sparse import csr_matrix
    from scipy.sparse.csgraph import shortest_path
    HAVE_SP = True
except ImportError:
    HAVE_SP = False

# is problem ko solve krny k lie main 2 mode le rha hoon
#  column major ids, fir is ke baad column range and the final one jo k hai contiguous id block
# graph hai undirected jo k unit edges k sath hue ga
#  aur hum current mode pr rhy gy ya fir spin kr jayeing gy, and bhai apnitou bs ho gayi hai
# yahan pr hum divide and conqueror wala rule follow kryn ta k problem statement divide hoti jaye

def _solve_scipy(N, M, Q, G, start, end, K):
    W2 = 2 * N
    V = M * W2
    g = np.array([list(row) for row in G]).reshape(N, M)
    act = np.stack([g != 'R', g != 'B'], axis=-1)            # act[r, c, mode]
    rr, cc, mm = np.meshgrid(np.arange(N), np.arange(M), np.arange(2), indexing='ij')
    sid = (cc * N + rr) * 2 + mm
    us, vs = [], []
    if M > 1:                                                  # horizontal moves
        ok = act[:, :-1, :] & act[:, 1:, :]
        us.append(sid[:, :-1, :][ok]); vs.append(sid[:, 1:, :][ok])
    if N > 1:                                                  # vertical moves
        ok = act[:-1, :, :] & act[1:, :, :]
        us.append(sid[:-1, :, :][ok]); vs.append(sid[1:, :, :][ok])
    ok = g == '.'                                              # spin
    us.append(sid[:, :, 0][ok]); vs.append(sid[:, :, 1][ok])
    u = np.concatenate(us); v = np.concatenate(vs)
    A = csr_matrix((np.ones(2 * u.size, dtype=np.float64),
                    (np.concatenate([u, v]), np.concatenate([v, u]))), shape=(V, V))
    actflat = np.zeros(V, dtype=bool)
    actflat[sid.ravel()] = act.ravel()

    sr = np.array([s[0] for s in start], dtype=np.int64)
    sc = np.array([s[1] for s in start], dtype=np.int64)
    er = np.array([e[0] for e in end], dtype=np.int64)
    ec = np.array([e[1] for e in end], dtype=np.int64)
    best = np.full(Q, np.inf)
    same = (sr == er) & (sc == ec)
    best[same] = 0.0

    leafw = max(4, 48 // N)
    stack = [(0, M - 1, np.nonzero(~same)[0])]
    while stack:
        lo, hi, qi = stack.pop()
        if qi.size == 0:
            continue
        base = lo * W2
        sub = A[base:(hi + 1) * W2, base:(hi + 1) * W2]
        qs = (sc[qi] * N + sr[qi]) * 2 - base                  # start state: blue mode
        qe = (ec[qi] * N + er[qi]) * 2 - base
        if hi - lo + 1 <= leafw:
            # Leaf: BFS directly from each distinct start inside this small range.
            us_, inv = np.unique(qs, return_inverse=True)
            D = shortest_path(sub, method='D', directed=True, unweighted=True, indices=us_)
            d = np.minimum(D[inv, qe], D[inv, qe + 1])
            best[qi] = np.minimum(best[qi], d)
            continue
        m = (lo + hi) // 2
        src = np.arange(m * W2, (m + 1) * W2)
        src = src[actflat[src]] - base
        if src.size:
            D = shortest_path(sub, method='D', directed=True, unweighted=True, indices=src)
            # Process queries in blocks to bound memory (|src| x block)
            B = 4096
            for j in range(0, qi.size, B):
                q = qi[j:j + B]
                a = D[:, qs[j:j + B]]
                b = np.minimum(D[:, qe[j:j + B]], D[:, qe[j:j + B] + 1])
                best[q] = np.minimum(best[q], (a + b).min(axis=0))
        L = (sc[qi] < m) & (ec[qi] < m)
        R = (sc[qi] > m) & (ec[qi] > m)
        stack.append((lo, m - 1, qi[L]))
        stack.append((m + 1, hi, qi[R]))

    Karr = np.array(K, dtype=np.float64)
    ok = best <= Karr
    return ["YES" if x else "NO" for x in ok.tolist()]


def _solve_python(N, M, Q, G, start, end, K):
    W2 = 2 * N
    V = M * W2
    act = [False] * V
    for c in range(M):
        for r in range(N):
            ch = G[r][c]
            i = (c * N + r) * 2
            act[i] = ch != 'R'
            act[i + 1] = ch != 'B'
    adjncy = [[] for _ in range(V)]
    for c in range(M):
        for r in range(N):
            i = (c * N + r) * 2
            for mode in (0, 1):
                x = i + mode
                if not act[x]:
                    continue
                if c + 1 < M and act[x + W2]:
                    adjncy[x].append(x + W2); adjncy[x + W2].append(x)
                if r + 1 < N and act[x + 2]:
                    adjncy[x].append(x + 2); adjncy[x + 2].append(x)
            if G[r][c] == '.':
                adjncy[i].append(i + 1); adjncy[i + 1].append(i)

    INF = float('inf')
    best = [INF] * Q
    qs = [(start[i][1] * N + start[i][0]) * 2 for i in range(Q)]
    qe = [(end[i][1] * N + end[i][0]) * 2 for i in range(Q)]
    scol = [s[1] for s in start]; ecol = [e[1] for e in end]

    def bfs(src, lo_id, hi_id):
        dist = {src: 0}
        dq = deque([src])
        while dq:
            x = dq.popleft()
            dx = dist[x] + 1
            for y in adjncy[x]:
                if lo_id <= y < hi_id and y not in dist:
                    dist[y] = dx
                    dq.append(y)
        return dist

    stack = [(0, M - 1, [i for i in range(Q) if qs[i] != qe[i]])]
    for i in range(Q):
        if qs[i] == qe[i]:
            best[i] = 0
    while stack:
        lo, hi, qi = stack.pop()
        if not qi:
            continue
        lo_id, hi_id = lo * W2, (hi + 1) * W2
        m = (lo + hi) // 2
        for s in range(m * W2, (m + 1) * W2):
            if not act[s]:
                continue
            d = bfs(s, lo_id, hi_id)
            for i in qi:
                a = d.get(qs[i])
                if a is None:
                    continue
                b = min(d.get(qe[i], INF), d.get(qe[i] + 1, INF))
                if a + b < best[i]:
                    best[i] = a + b
        stack.append((lo, m - 1, [i for i in qi if scol[i] < m and ecol[i] < m]))
        stack.append((m + 1, hi, [i for i in qi if scol[i] > m and ecol[i] > m]))
    return ["YES" if best[i] <= K[i] else "NO" for i in range(Q)]
    #  now hum apnay hisaab se cheezyn set kr chuky hian 


def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:    
    if HAVE_SP:
        return _solve_scipy(N, M, Q, G, start, end, K)
    return _solve_python(N, M, Q, G, start, end, K)
    # main k funtion pr janay se pehllay hamaray saray functions ready hain

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