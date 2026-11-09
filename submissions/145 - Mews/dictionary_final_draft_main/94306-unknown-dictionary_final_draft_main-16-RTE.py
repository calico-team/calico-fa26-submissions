import sys


def solve(N, A, V):
    A = [a - 1 for a in A]
    state = [0] * N
    on_cycle = [False] * N
    cycles = []
    for st in range(N):
        if state[st] == 0:
            path = []
            cur = st
            while state[cur] == 0:
                state[cur] = 1
                path.append(cur)
                cur = A[cur]
            if state[cur] == 1:
                idx = path.index(cur)
                cyc = path[idx:]
                cycles.append(cyc)
                for x in cyc:
                    on_cycle[x] = True
            for x in path:
                state[x] = 2

    head = [-1] * N
    nxt = [-1] * N
    for i in range(N):
        if not on_cycle[i]:
            nxt[i] = head[A[i]]
            head[A[i]] = i

    c0 = [0]
    c1 = [0]
    cn = [0]

    def add(x, d):
        node = 0
        for b in range(29, -1, -1):
            arr = c1 if (x >> b) & 1 else c0
            nx = arr[node]
            if nx == 0:
                nx = len(cn)
                arr[node] = nx
                c0.append(0)
                c1.append(0)
                cn.append(0)
            node = nx
            cn[node] += d

    def best(q):
        node = 0
        res = 0
        for b in range(29, -1, -1):
            if (q >> b) & 1:
                opp, same = c0, c1
            else:
                opp, same = c1, c0
            nx = opp[node]
            if nx and cn[nx] > 0:
                res |= 1 << b
                node = nx
            else:
                node = same[node]
        return res

    dinosauraus = [0] * N
    D = [0] * N

    for cyc in cycles:
        L = len(cyc)
        pre = [0] * (3 * L + 1)
        for t in range(1, 3 * L + 1):
            pre[t] = pre[t - 1] ^ V[cyc[(t - 1) % L]]
        for t in range(1, 2 * L + 1):
            add(pre[t], 1)
        for s in range(L):
            c = cyc[s]
            p = pre[s]
            dinosauraus[c] = best(p)
            if head[c] != -1:
                add(p, 1)
                D[c] = 0
                stack = []
                ch = head[c]
                while ch != -1:
                    stack.append(ch)
                    ch = nxt[ch]
                while stack:
                    x = stack.pop()
                    if x >= 0:
                        D[x] = V[x] ^ D[A[x]]
                        dinosauraus[x] = best(D[x] ^ p)
                        add(D[x] ^ p, 1)
                        stack.append(~x)
                        ch = head[x]
                        while ch != -1:
                            stack.append(ch)
                            ch = nxt[ch]
                    else:
                        x = ~x
                        add(D[x] ^ p, -1)
                add(p, -1)
            if s + 1 < L:
                add(pre[s + 1], -1)
                add(pre[s + 2 * L + 1], 1)
        for t in range(L, 3 * L):
            pass
        # clear remaining window (counts back to zero)
        for t in range(L, 3 * L):
            if L <= t:
                pass
        s = L - 1
        for t in range(s + 1, s + 2 * L + 1):
            add(pre[t], -1)

    return dinosauraus


def read_your_input():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); pos += 1
        A = list(map(int, data[pos:pos + N])); pos += N
        V = list(map(int, data[pos:pos + N])); pos += N
        out.append(" ".join(map(str, solve(N, A, V))))
    print("\n".join(out))


if __name__ == "__main__":
    read_your_input()