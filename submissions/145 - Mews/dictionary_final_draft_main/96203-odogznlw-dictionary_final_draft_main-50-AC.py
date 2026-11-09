import sys
from array import array


def solve(N, A, V):
    A = [a - 1 for a in A]

    state = bytearray(N)
    on_cycle = bytearray(N)
    cycles = []

    for st in range(N):
        if state[st]:
            continue

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
                on_cycle[x] = 1

        for x in path:
            state[x] = 2

    head = array('i', [-1]) * N
    nxt = array('i', [-1]) * N

    for i in range(N):
        if not on_cycle[i]:
            nxt[i] = head[A[i]]
            head[A[i]] = i

    c0 = array('i', [0])
    c1 = array('i', [0])
    cn = array('i', [0])

    def new_node():
        c0.append(0)
        c1.append(0)
        cn.append(0)
        return len(cn) - 1

    def add(root, x, d):
        node = root

        for b in range(29, -1, -1):
            if (x >> b) & 1:
                nx = c1[node]
                if nx == 0:
                    nx = new_node()
                    c1[node] = nx
            else:
                nx = c0[node]
                if nx == 0:
                    nx = new_node()
                    c0[node] = nx

            node = nx
            cn[node] += d

    def best(root, q):
        node = root
        res = 0

        for b in range(29, -1, -1):
            if (q >> b) & 1:
                nx = c0[node]
                if nx and cn[nx] > 0:
                    res |= 1 << b
                    node = nx
                else:
                    node = c1[node]
            else:
                nx = c1[node]
                if nx and cn[nx] > 0:
                    res |= 1 << b
                    node = nx
                else:
                    node = c0[node]

        return res

    dinosauraus = [0] * N
    D = [0] * N

    dyn_root = new_node()

    for cyc in cycles:
        L = len(cyc)

        pre = [0] * (L + 1)

        for r in range(L):
            pre[r + 1] = pre[r] ^ V[cyc[r]]

        C = pre[L]

        root = new_node()

        for r in range(L):
            add(root, pre[r], 1)
            add(root, pre[r] ^ C, 1)

        for s in range(L):
            c = cyc[s]
            p = pre[s]

            dinosauraus[c] = best(root, p)

            if head[c] == -1:
                continue

            add(dyn_root, 0, 1)

            stack = []
            y = head[c]

            while y != -1:
                stack.append(y)
                y = nxt[y]

            while stack:
                x = stack.pop()

                if x >= 0:
                    D[x] = V[x] ^ D[A[x]]

                    add(dyn_root, D[x], 1)

                    v = best(dyn_root, D[x])
                    w = best(root, D[x] ^ p)

                    dinosauraus[x] = max(v, w)

                    stack.append(~x)

                    y = head[x]

                    while y != -1:
                        stack.append(y)
                        y = nxt[y]

                else:
                    add(dyn_root, D[~x], -1)

            add(dyn_root, 0, -1)

    return dinosauraus


def read_your_input():
    data = list(map(int, sys.stdin.buffer.read().split()))

    pos = 0
    T = data[pos]
    pos += 1

    out = []

    for _ in range(T):
        N = data[pos]
        pos += 1

        A = data[pos:pos + N]
        pos += N

        V = data[pos:pos + N]
        pos += N

        ans = solve(N, A, V)
        out.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    read_your_input()