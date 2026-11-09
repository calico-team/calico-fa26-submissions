try:
    import numpy as np
    HAVE_NP = True
except ImportError:
    HAVE_NP = False

from math import isqrt


def _solve_python(N, M, Q, earthquakes):
    # as this is reverse order so qurk ka covering cell win kry ga is wjh se last se paint kryn gy aur cell ko dobara paint nahi kryn gy
    NM = N * M
    nextt = list(range(NM + 1))
    win = [-1] * NM
    best_at_center = {}          # agr center main tou hum is qurk ko skip kr dyn gy
    for t in range(Q - 1, -1, -1):
        R, C, P = earthquakes[t]
        key = R * M + C
        if best_at_center.get(key, -1) >= P:
            continue
        best_at_center[key] = P
        PP = P * P
        for dr in range(-P, P + 1):
            w = isqrt(PP - dr * dr)
            base = (R + dr) * M + C
            low = base - w
            high = base + w
            # find(low) with path compression
            i = low
            while nextt[i] != i:
                i = nextt[i]
            j = low
            while nextt[j] != i:
                nextt[j], j = i, nextt[j]
            while i <= high:
                win[i] = t
                # union i -> i+1, then find
                k = i + 1
                while nextt[k] != k:
                    k = nextt[k]
                nextt[i] = k
                i = k
            nextt[low] = i
    out = []
    for r in range(N):
        row = [0] * M
        off = r * M
        for c in range(M):
            t = win[off + c]
            if t >= 0:
                R, C, P = earthquakes[t]
                row[c] = P * P - (r - R) ** 2 - (c - C) ** 2 + 1
        out.append(row)
    return out


def _solve_numpy(N, M, Q, earthquakes):
    # har aik row ko index |t| ko use krty hue mention kr rha hoon
    # range ko out maxx honay pr 2 ka floor add kronga
    # ab minium stage pr lanay k lie is ko force kronga ta k cell wapis 0 pr aa jaye
    NM = N * M
    E = np.array(earthquakes, dtype=np.int64).reshape(-1, 3)
    R, C, P = E[:, 0], E[:, 1], E[:, 2]
    cnt = 2 * P + 1
    L = int(cnt.max()).bit_length()          # levels 0 to L-1
    lg = np.zeros(int(cnt.max()) + 2, dtype=np.int64)
    for v in range(2, len(lg)):
        lg[v] = lg[v >> 1] + 1
    tab = np.zeros(L * NM, dtype=np.int32)

    CHUNK = 1 << 17
    starts = np.concatenate(([0], np.cumsum(cnt)))
    q0 = 0
    while q0 < Q:
        q1 = int(np.searchsorted(starts, starts[q0] + CHUNK, side='right')) - 1
        q1 = max(q1, q0 + 1)
        q1 = min(q1, Q)
        c = cnt[q0:q1]
        qid = np.repeat(np.arange(q0, q1), c)
        dr = np.arange(qid.size, dtype=np.int64) - (starts[qid] - starts[q0]) - P[qid]
        x = P[qid] * P[qid] - dr * dr
        w = np.sqrt(x).astype(np.int64)
        w -= (w * w > x)
        w += ((w + 1) * (w + 1) <= x)
        ln = 2 * w + 1
        k = lg[ln]
        pos = (R[qid] + dr) * M + C[qid] - w
        tval = (qid + 1).astype(np.int32)
        np.maximum.at(tab, k * NM + pos, tval)
        np.maximum.at(tab, k * NM + pos + ln - (np.int64(1) << k), tval)
        q0 = q1

    tab = tab.reshape(L, NM)
    for kk in range(L - 1, 0, -1):
        h = 1 << (kk - 1)
        np.maximum(tab[kk - 1], tab[kk], out=tab[kk - 1])
        np.maximum(tab[kk - 1][h:], tab[kk][:NM - h], out=tab[kk - 1][h:])
    win = tab[0].astype(np.int64)
    idx = np.maximum(win - 1, 0)
    cells = np.arange(NM, dtype=np.int64)
    rr = cells // M
    cc = cells % M
    val = P[idx] * P[idx] - (rr - R[idx]) ** 2 - (cc - C[idx]) ** 2 + 1
    val[win == 0] = 0
    return val.reshape(N, M).tolist()

def solve(N, M, Q, earthquakes):
    # solution is almost ready is k baad hum basic si information lyn gy
    work = 0
    for _, _, P in earthquakes:
        work += 2 * P + 1
    if HAVE_NP and work + N * M > 4000:
        return _solve_numpy(N, M, Q, earthquakes)
    return _solve_python(N, M, Q, earthquakes)


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()