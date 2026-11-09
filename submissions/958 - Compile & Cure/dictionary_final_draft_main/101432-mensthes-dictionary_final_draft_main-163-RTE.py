import sys

def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """

    A0 = [a - 1 for a in A]
    BITS = 30

    ch0 = [0]
    ch1 = [0]
    cnt = [0]
    free = []
    ch = (ch0, ch1)

    def reset():
        ch0[:] = [0]
        ch1[:] = [0]
        cnt[:] = [0]
        free.clear()

    def insert(v):
        node = 0
        for b in range(BITS - 1, -1, -1):
            bit = (v >> b) & 1
            arr = ch[bit]
            nxt = arr[node]
            if nxt == 0:
                if free:
                    nxt = free.pop()
                    ch0[nxt] = 0
                    ch1[nxt] = 0
                    cnt[nxt] = 0
                else:
                    nxt = len(cnt)
                    ch0.append(0)
                    ch1.append(0)
                    cnt.append(0)
                arr[node] = nxt
            cnt[nxt] += 1
            node = nxt

    def remove(v):
        node = 0
        for b in range(BITS - 1, -1, -1):
            bit = (v >> b) & 1
            arr = ch[bit]
            nxt = arr[node]
            cnt[nxt] -= 1
            if cnt[nxt] == 0:
                arr[node] = 0
                free.append(nxt)
            node = nxt

    def query(q):
        node = 0
        res = 0
        for b in range(BITS - 1, -1, -1):
            bit = (q >> b) & 1
            want = ch[1 - bit][node]
            if want:
                res |= (1 << b)
                node = want
            else:
                node = ch[bit][node]
        return res

    color = [0] * N
    on_cycle = [False] * N
    cycles = []
    for s in range(N):
        if color[s]:
            continue
        path = []
        x = s
        while color[x] == 0:
            color[x] = 1
            path.append(x)
            x = A0[x]
        if color[x] == 1:
            idx = path.index(x)
            cyc = path[idx:]
            for c in cyc:
                on_cycle[c] = True
            cycles.append(cyc)
        for y in path:
            color[y] = 2

    children = [[] for _ in range(N)]
    for i in range(N):
        if not on_cycle[i]:
            children[A0[i]].append(i)

    ans = [0] * N
    T = [0] * N

    for cyc in cycles:
        L = len(cyc)
        Z = [0] * (3 * L + 1)
        for t in range(3 * L):
            Z[t + 1] = Z[t] ^ V[cyc[t % L]]

        reset()
        for t in range(1, 2 * L + 1):
            insert(Z[t])

        for j in range(L):
            zj = Z[j]
            c = cyc[j]
            ans[c] = query(zj)

            insert(zj)
            stack = list(children[c])
            while stack:
                x = stack.pop()
                if x >= 0:
                    T[x] = V[x] ^ T[A0[x]]
                    val = T[x] ^ zj
                    ans[x] = query(val)
                    insert(val)
                    stack.append(~x)
                    stack.extend(children[x])
                else:
                    x = ~x
                    remove(T[x] ^ zj)
            remove(zj)

            if j < L - 1:
                remove(Z[j + 1])
                insert(Z[j + 2 * L + 1])

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