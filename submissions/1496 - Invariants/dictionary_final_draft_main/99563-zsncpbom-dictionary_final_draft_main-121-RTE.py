def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    nxt = [a - 1 for a in A]
    rev = [[] for _ in range(N)]
    state = [0] * N  
    cycles = []
    for s in range(N):
        if state[s]:
            continue
        path = []
        u = s
        while state[u] == 0:
            state[u] = 1
            path.append(u)
            u = nxt[u]
        if state[u] == 1:
            cycles.append(path[path.index(u):])
        for v in path:
            state[v] = 2
    on_cycle = [False] * N
    for cyc in cycles:
        for c in cyc:
            on_cycle[c] = True
    for u in range(N):
        if not on_cycle[u]:
            rev[nxt[u]].append(u)
    
    shifts = list(range(28, -1, -2))
    best = [0] * 64
    for m in range(1, 16):
        for d in range(4):
            best[m * 4 + d] = max((c for c in range(4) if m >> c & 1), key=lambda c: c ^ d)
    ch = [0] * 4
    cnt = [0]
    mask = [0]
    
    def add(x):
        node = 0
        for s in shifts:
            c = x >> s & 3
            i = 4 * node + c
            child = ch[i]
            if not child:
                child = len(cnt)
                ch[i] = child
                ch.extend((0, 0, 0, 0))
                cnt.append(0)
                mask.append(0)
            mask[node] |= 1 << c
            cnt[child] += 1
            node = child
    
    def remove(x):
        node = 0
        for s in shifts:
            c = x >> s & 3
            child = ch[4 * node + c]
            cnt[child] -= 1
            if not cnt[child]:
                mask[node] ^= 1 << c
            node = child
    
    def query(x):
        node = 0
        res = 0
        for s in shifts:
            d = x >> s & 3
            c = best[4 * mask[node] + d]
            res = res << 2 | (c ^ d)
            node = ch[4 * node + c]
        return res
    
    ans = [0] * N
    Y = [0] * N
    for cyc in cycles:
        members = list(cyc)
        for u in members:
            members.extend(rev[u])
        size = len(members)
    
        if size <= 20:
            for u in members:
                h = top = 0
                x = u
                for _ in range(2 * size):
                    h ^= V[x]
                    if h > top:
                        top = h
                    x = nxt[x]
                ans[u] = top
            continue
    
        Q = []
        acc = 0
        for c in cyc:
            Q.append(acc)
            acc ^= V[c]
        W = set(Q) | {q ^ acc for q in Q}
    
        ch = [0] * 4
        cnt = [0]
        mask = [0]
        for w in W:
            add(w)
        for c, q in zip(cyc, Q):
            Y[c] = q
            ans[c] = query(q)
        for c in cyc:
            stack = list(rev[c])
            while stack:
                u = stack.pop()
                if u < 0:
                    remove(Y[~u])
                    continue
                y = V[u] ^ Y[nxt[u]]
                Y[u] = y
                ans[u] = query(y)
                add(y)
                stack.append(~u)
                stack.extend(rev[u])
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
