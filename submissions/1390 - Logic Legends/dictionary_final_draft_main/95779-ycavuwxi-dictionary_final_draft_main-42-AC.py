from array import array
from bisect import bisect_left
 
 
def cycle_max(D, x):
    lo = 0
    hi = len(D)
    prefix = 0
    res = 0
    for b in range(29, -1, -1):
        bit = 1 << b
        mid = bisect_left(D, prefix | bit, lo, hi)
        if x & bit:
            if lo < mid:
                hi = mid
                res |= bit
            else:
                lo = mid
                prefix |= bit
        else:
            if mid < hi:
                lo = mid
                prefix |= bit
                res |= bit
            else:
                hi = mid
    return res
 
 
def solve(N, A, V):
    nxt = [a - 1 for a in A]
    indeg = [0] * N
    for u in nxt:
        indeg[u] += 1
    on_cycle = [True] * N
    queue = [i for i in range(N) if indeg[i] == 0]
    for i in queue:
        on_cycle[i] = False
    for u in queue:
        v = nxt[u]
        indeg[v] -= 1
        if indeg[v] == 0:
            on_cycle[v] = False
            queue.append(v)
 
    cyc_id = [-1] * N
    pk = [0] * N
    sets = []
    seen = [False] * N
    for i in range(N):
        if on_cycle[i] and not seen[i]:
            nodes = []
            u = i
            while not seen[u]:
                seen[u] = True
                nodes.append(u)
                u = nxt[u]
            P = [0]
            for u in nodes:
                P.append(P[-1] ^ V[u])
            C = P[-1]
            D = []
            for r in range(1, len(P)):
                D.append(P[r])
                D.append(P[r] ^ C)
            D.sort()
            for j, u in enumerate(nodes):
                cyc_id[u] = len(sets)
                pk[u] = P[j]
            sets.append(D)
 
    kids = [[] for _ in range(N)]
    for i in range(N):
        if not on_cycle[i]:
            kids[nxt[i]].append(i)
 
    size = (N + 2) * 31
    c0 = array('i', [0]) * size
    c1 = array('i', [0]) * size
    cnt = array('i', [0]) * size
    used = [1]
 
    def update(x, d):
        cur = 0
        for b in range(29, -1, -1):
            if (x >> b) & 1:
                arr = c1
            else:
                arr = c0
            nx = arr[cur]
            if nx == 0:
                nx = used[0]
                used[0] += 1
                arr[cur] = nx
            cur = nx
            cnt[cur] += d
 
    def query(x):
        cur = 0
        res = 0
        for b in range(29, -1, -1):
            if (x >> b) & 1:
                want = c0
                other = c1
            else:
                want = c1
                other = c0
            nx = want[cur]
            if nx and cnt[nx] > 0:
                res |= 1 << b
                cur = nx
            else:
                cur = other[cur]
        return res
 
    ans = [0] * N
    G = [0] * N
    for c in range(N):
        if not on_cycle[c]:
            continue
        D = sets[cyc_id[c]]
        base = pk[c]
        ans[c] = cycle_max(D, base)
        if not kids[c]:
            continue
        update(0, 1)
        stack = [(c, 0)]
        while stack:
            u, idx = stack.pop()
            if idx < len(kids[u]):
                stack.append((u, idx + 1))
                v = kids[u][idx]
                G[v] = V[v] ^ G[u]
                ans[v] = max(query(G[v]), cycle_max(D, G[v] ^ base))
                update(G[v], 1)
                stack.append((v, 0))
            else:
                if u != c:
                    update(G[u], -1)
        update(0, -1)
    return ans
 
 
def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))
 
 
if __name__ == '__main__':
    main()