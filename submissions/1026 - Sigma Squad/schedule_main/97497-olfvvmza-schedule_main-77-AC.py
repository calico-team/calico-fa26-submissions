import sys
import heapq

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    res = []
    for _ in range(t):
        n, m, k = int(data[p]), int(data[p+1]), int(data[p+2]); p += 3
        par = [0] + [int(x) for x in data[p:p+n]]; p += n

        ch = [[] for _ in range(n+1)]
        for i in range(1, n+1):
            ch[par[i]].append(i)

        order = []
        st = [0]
        while st:
            u = st.pop()
            order.append(u)
            for v in ch[u]:
                st.append(v)
        h = [0] * (n+1)
        for u in reversed(order):
            for v in ch[u]:
                h[u] = max(h[u], h[v] + 1)

        pq = [(-h[v], v) for v in ch[0]]
        heapq.heapify(pq)
        ans = 0
        for _ in range(m):
            if not pq:
                break
            took = []
            while pq and len(took) < k:
                took.append(heapq.heappop(pq)[1])
            ans += len(took)
            for u in took:
                for v in ch[u]:
                    heapq.heappush(pq, (-h[v], v))
        res.append(ans)
    print('\n'.join(map(str, res)))

main()
