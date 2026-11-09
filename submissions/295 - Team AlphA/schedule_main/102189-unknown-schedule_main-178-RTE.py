def solve():
    t = int(input())
    for _ in range(t):
        n, m, k = map(int, input().split())
        p = list(map(int, input().split()))
        graph = [[] for _ in range(n + 1)]
        ready = []
        for i in range(1, n + 1):
            if p[i - 1] == 0:
                ready.append(i)
            else:
                graph[p[i - 1]].append(i)
        ans = 0
        for _ in range(m):
            if not ready:
                break
            nxt = []
            for u in ready[:k]:
                ans += 1
                nxt += graph[u]
            ready = ready[k:] + nxt
        print(ans)
solve()
if __name__ == "__main__":
    solve()