import sys


def solve(N, M, K, P):
    head = [-1] * (N + 1)
    nxt = [-1] * (N + 1)
    for i in range(N, 0, -1):
        p = P[i - 1]
        if p < 0 or p > N or p == i:
            p = 0
        nxt[i] = head[p]
        head[p] = i
    cnt = [0] * (N + 2)
    depth = [0] * (N + 1)
    queue = [0]
    qi = 0
    while qi < len(queue):
        u = queue[qi]
        qi += 1
        d = depth[u] + 1
        c = head[u]
        while c != -1:
            depth[c] = d
            cnt[d] += 1
            queue.append(c)
            c = nxt[c]
    total = 0
    mn = K * M + 1
    D = 1
    while D <= N and cnt[D] > 0:
        cap = K * (M - D + 1)
        if cap < mn:
            mn = cap
        nd = cnt[D]
        if mn < nd:
            return total + (mn if mn > 0 else 0)
        total += nd
        mn -= nd
        D += 1
    return total


def tokens():
    for line in sys.stdin.buffer:
        for tok in line.split():
            yield int(tok)


def main():
    it = tokens()
    T = next(it, None)
    if T is None:
        return
    out = []
    for _ in range(T):
        N = next(it, None)
        M = next(it, None)
        K = next(it, None)
        if K is None:
            break
        P = [0] * N
        for i in range(N):
            v = next(it, None)
            if v is None:
                break
            P[i] = v
        out.append(str(solve(N, M, K, P)))
    sys.stdout.write("\n".join(out) + ("\n" if out else ""))


main()
