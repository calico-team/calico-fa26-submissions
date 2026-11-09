def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
import sys
from array import array

MASKS = tuple(1 << b for b in range(29, -1, -1))


def solve(N, A, V):
    A = [a - 1 for a in A]
    ans = [0] * N

    # ---- find cycles of the functional graph (iteratively) ----
    state = [0] * N          # 0 new, 1 on current path, 2 finished
    pos = [0] * N
    oncycle = [False] * N
    cycles = []
    for s in range(N):
        if state[s]:
            continue
        path = []
        u = s
        while state[u] == 0:
            state[u] = 1
            pos[u] = len(path)
            path.append(u)
            u = A[u]
        if state[u] == 1:
            cyc = path[pos[u]:]
            cycles.append(cyc)
            for c in cyc:
                oncycle[c] = True
        for x in path:
            state[x] = 2

    kids = [[] for _ in range(N)]
    for i in range(N):
        if not oncycle[i]:
            kids[A[i]].append(i)

    ch = array('i', bytes(4 * 4096))
    D = [0] * N
    ufirst = [0] * N
    usaved = [0] * N

    for cyc in cycles:
        c = len(cyc)
        F = [0] * c
        x = 0
        for m in range(c):
            F[m] = x
            x ^= V[cyc[m]]
        C = x
        U = set(F)
        U.update(f ^ C for f in F)

        # trie nodes are stored "doubled": child slot = node + bit, 0 means null
        fp = 2
        if fp + 64 > len(ch):
            ch.extend(array('i', bytes(4 * len(ch))))
        rootU = fp
        ch[fp] = 0; ch[fp + 1] = 0
        fp += 2
        for v in U:
            if fp + 64 > len(ch):
                ch.extend(array('i', bytes(4 * len(ch))))
            node = rootU
            for m in MASKS:
                s = node + 1 if v & m else node
                nx = ch[s]
                if nx:
                    node = nx
                else:
                    ch[s] = fp
                    node = fp
                    ch[fp] = 0; ch[fp + 1] = 0
                    fp += 2

        def qU(xv):
            node = rootU
            res = 0
            for m in MASKS:
                if xv & m:
                    nx = ch[node]
                    if nx:
                        res |= m; node = nx
                    else:
                        node = ch[node + 1]
                else:
                    nx = ch[node + 1]
                    if nx:
                        res |= m; node = nx
                    else:
                        node = ch[node]
            return res

        # ancestor trie, initially holding just the value 0 (the cycle entry node)
        if fp + 64 > len(ch):
            ch.extend(array('i', bytes(4 * len(ch))))
        rootA = fp
        ch[fp] = 0; ch[fp + 1] = 0
        fp += 2
        node = rootA
        for m in MASKS:
            ch[node] = fp
            node = fp
            ch[fp] = 0; ch[fp + 1] = 0
            fp += 2

        for s in range(c):
            r = cyc[s]
            fs = F[s]
            ans[r] = qU(fs)
            stack = list(kids[r])
            while stack:
                i = stack.pop()
                if i >= 0:
                    d = V[i] ^ D[A[i]]
                    D[i] = d
                    # best over ancestors in the tail
                    node = rootA
                    res = 0
                    for m in MASKS:
                        if d & m:
                            nx = ch[node]
                            if nx:
                                res |= m; node = nx
                            else:
                                node = ch[node + 1]
                        else:
                            nx = ch[node + 1]
                            if nx:
                                res |= m; node = nx
                            else:
                                node = ch[node]
                    r2 = qU(d ^ fs)
                    ans[i] = res if res > r2 else r2
                    # insert d (undo is O(1))
                    if fp + 64 > len(ch):
                        ch.extend(array('i', bytes(4 * len(ch))))
                    usaved[i] = fp
                    first = -1
                    node = rootA
                    for m in MASKS:
                        s2 = node + 1 if d & m else node
                        nx = ch[s2]
                        if nx:
                            node = nx
                        else:
                            if first < 0:
                                first = s2
                            ch[s2] = fp
                            node = fp
                            ch[fp] = 0; ch[fp + 1] = 0
                            fp += 2
                    ufirst[i] = first
                    stack.append(~i)
                    stack.extend(kids[i])
                else:
                    i = ~i
                    f = ufirst[i]
                    if f >= 0:
                        ch[f] = 0
                        fp = usaved[i]
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
