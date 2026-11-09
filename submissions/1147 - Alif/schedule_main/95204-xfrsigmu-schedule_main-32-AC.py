import sys
import heapq

def go(N, M, K, P):
    ch = [[] for _ in range(N + 1)]
    roots = []
    for i in range(1, N + 1):
        if P[i]:
            ch[P[i]].append(i)
        else:
            roots.append(i)

    # walk from roots to get a valid parent-before-child order
    order = []
    st = roots[:]
    while st:
        u = st.pop()
        order.append(u)
        st.extend(ch[u])

    sz = [1] * (N + 1)
    for u in reversed(order):
        if P[u]:
            sz[P[u]] += sz[u]

    # biggest subtree first (heapq is min-heap, so negate)
    h = [(-sz[r], r) for r in roots]
    heapq.heapify(h)

    total = 0
    sem = 0
    while h and sem < M:
        sem += 1
        took = []
        for _ in range(K):
            if not h:
                break
            _, u = heapq.heappop(h)
            took.append(u)
        total += len(took)
        # kids only unlock next semester, not this one
        for u in took:
            for c in ch[u]:
                heapq.heappush(h, (-sz[c], c))

    return total

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    res = []
    for _ in range(T):
        N, M, K = int(d[p]), int(d[p+1]), int(d[p+2])
        p += 3
        P = [0] * (N + 1)
        for i in range(1, N + 1):
            P[i] = int(d[p]); p += 1
        res.append(str(go(N, M, K, P)))
    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()