import sys
from array import array


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    levels = tuple(range(28, -1, -2))
    pw = [4 ** d for d in range(1, 16)]
    ch = array('i', [0]) * 64
    z4 = array('i', [0]) * 4
    out = []

    for _ in range(t):
        n = int(data[pos]); pos += 1
        a = [int(x) - 1 for x in data[pos:pos + n]]; pos += n
        v = list(map(int, data[pos:pos + n])); pos += n

        state = [0] * n
        cycles = []
        for s in range(n):
            if state[s]:
                continue
            path = []
            x = s
            while not state[x]:
                state[x] = 1
                path.append(x)
                x = a[x]
            if state[x] == 1:
                cycles.append(path[path.index(x):])
            for y in path:
                state[y] = 2

        need = 2
        for cyc in cycles:
            m = 2 * len(cyc)
            if m > 12:
                need += 1 + sum([m if p > m else p for p in pw])
            for y in cyc:
                state[y] = 3
        children = [[] for _ in range(n)]
        internal = 0
        for x in range(n):
            if state[x] != 3:
                cx = children[a[x]]
                if not cx and state[a[x]] != 3:
                    internal += 1
                cx.append(x)
        need += 16 * internal
        if len(ch) < 4 * need:
            ch.extend(array('i', [0]) * (4 * need - len(ch)))

        ans = [0] * n
        pot = [0] * n
        ver = [0] * n
        cnt = 1

        for cyc in cycles:
            q = []
            acc = 0
            for y in cyc:
                acc ^= v[y]
                q.append(acc)
            C = acc
            W = set(q)
            W.update([x ^ C for x in q])

            small = len(W) <= 12
            if small:
                Wl = list(W)
                root = 0
            else:
                root = cnt; cnt += 1
                ch[root * 4:root * 4 + 4] = z4
                pth = [root] * 16
                prev = -1
                for x in sorted(W):
                    d = 0 if prev < 0 else (30 - (x ^ prev).bit_length()) >> 1
                    prev = x
                    node = pth[d]
                    while d < 15:
                        nn = cnt; cnt += 1
                        b = nn << 2
                        ch[b:b + 4] = z4
                        ch[(node << 2) + ((x >> (28 - 2 * d)) & 3)] = nn
                        d += 1
                        pth[d] = nn
                        node = nn

            prev = 0
            stack = []
            for i, c in enumerate(cyc):
                key = prev
                prev = q[i]
                pot[c] = key
                ver[c] = root
                if small:
                    ans[c] = max([key ^ w for w in Wl])
                else:
                    node = root
                    res = 0
                    for k in levels:
                        w = 3 ^ ((key >> k) & 3)
                        b = node << 2
                        nx = ch[b + w]
                        if nx:
                            res |= 3 << k
                        else:
                            nx = ch[b + (w ^ 1)]
                            if nx:
                                res |= 2 << k
                            else:
                                nx = ch[b + (w ^ 2)]
                                if nx:
                                    res |= 1 << k
                                else:
                                    nx = ch[b + (w ^ 3)]
                        node = nx
                    ans[c] = res
                if children[c]:
                    stack.extend(children[c])

            while stack:
                x = stack.pop()
                p = a[x]
                key = v[x] ^ pot[p]
                pot[x] = key
                res = max([key ^ w for w in Wl]) if small else 0
                proot = ver[p]
                if proot:
                    node = proot
                    r2 = 0
                    for k in levels:
                        w = 3 ^ ((key >> k) & 3)
                        b = node << 2
                        nx = ch[b + w]
                        if nx:
                            r2 |= 3 << k
                        else:
                            nx = ch[b + (w ^ 1)]
                            if nx:
                                r2 |= 2 << k
                            else:
                                nx = ch[b + (w ^ 2)]
                                if nx:
                                    r2 |= 1 << k
                                else:
                                    nx = ch[b + (w ^ 3)]
                        node = nx
                    if r2 > res:
                        res = r2
                ans[x] = res
                cx = children[x]
                if cx:
                    old = proot
                    new = cnt
                    ver[x] = new
                    for k in levels:
                        o4 = old << 2
                        n4 = new << 2
                        ch[n4:n4 + 4] = ch[o4:o4 + 4]
                        d = (key >> k) & 3
                        new += 1
                        ch[n4 + d] = new
                        old = ch[o4 + d]
                    cnt = new + 1
                    stack.extend(cx)

        out.append(' '.join(map(str, ans)))

    sys.stdout.write('\n'.join(out) + '\n')


main()
