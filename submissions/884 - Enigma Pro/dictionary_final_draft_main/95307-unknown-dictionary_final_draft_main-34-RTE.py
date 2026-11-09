import sys
from array import array

LEVELS = tuple(range(28, -1, -2))


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    tests = []
    maxn = 0
    for _ in range(t):
        n = int(data[pos]); pos += 1
        tests.append((n, data[pos:pos + n], data[pos + n:pos + 2 * n]))
        pos += 2 * n
        if n > maxn:
            maxn = n
    del data


    ch = array('i', [0]) * (4 * (16 * maxn + 2))
    levels = LEVELS
    out = []

    for n, ra, rv in tests:
        a = [int(x) - 1 for x in ra]
        v = list(map(int, rv))


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

        for cyc in cycles:
            for y in cyc:
                state[y] = 3
        children = [[] for _ in range(n)]
        for x in range(n):
            if state[x] != 3:
                children[a[x]].append(x)

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
            else:
                PS = [{x >> k for x in W} for k in levels]
                LP = tuple(zip(levels, PS))

            prev = 0
            stack = []
            for i, c in enumerate(cyc):
                key = prev
                prev = q[i]
                pot[c] = key
                if small:
                    ans[c] = max([key ^ w for w in Wl])
                else:
                    p = 0
                    for k, s in LP:
                        cc = (p << 2) | (3 ^ ((key >> k) & 3))
                        if cc in s:
                            p = cc
                        elif cc ^ 1 in s:
                            p = cc ^ 1
                        elif cc ^ 2 in s:
                            p = cc ^ 2
                        else:
                            p = cc ^ 3
                    ans[c] = p ^ key
                if children[c]:
                    stack.extend(children[c])

            while stack:
                x = stack.pop()
                p = a[x]
                key = v[x] ^ pot[p]
                pot[x] = key
                if small:
                    res = max([key ^ w for w in Wl])
                else:
                    p2 = 0
                    for k, s in LP:
                        cc = (p2 << 2) | (3 ^ ((key >> k) & 3))
                        if cc in s:
                            p2 = cc
                        elif cc ^ 1 in s:
                            p2 = cc ^ 1
                        elif cc ^ 2 in s:
                            p2 = cc ^ 2
                        else:
                            p2 = cc ^ 3
                    res = p2 ^ key
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
