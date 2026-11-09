import sys

def solve(N,M, Q,G, start,end, K):
    stride = 2*N
    graph = [[] for _ in range(stride*M)]
    cuts = [[] for _ in range(M-1)]
    tiles = [0]*(N*M)

    for c in range(M):
        for r in range(N):
            tile = G[r][c]
            tiles[c*N+r] = 1 if tile == "B" else 2 if tile == "R" else 3

    for c in range(M):
        for r in range(N):
            cell = c*N+r
            tile = tiles[cell]
            u = 2*cell

            if tile == 3:
                graph[u].append(u+1)
                graph[u+1].append(u)

            if r+1 < N:
                both = tile & tiles[cell+1]
                if both & 1:
                    graph[u].append(u+2)
                    graph[u+2].append(u)
                if both & 2:
                    graph[u+1].append(u+3)
                    graph[u+3].append(u+1)
            if c+1 < M:
                v = u+stride
                both = tile & tiles[cell+N]
                if both & 1:
                    graph[u].append(v)
                    graph[v].append(u)
                    cuts[c].append((u, v))
                if both & 2:
                    graph[u+1].append(v+1)
                    graph[v+1].append(u+1)
                    cuts[c].append((u+1, v+1))

    answer = ["NO"]*Q
    queries = []
    for i in range(Q):
        r1,c1 = start[i]
        r2,c2 = end[i]
        limit = K[i]
        if r1 == r2 and c1 == c2:
            answer[i] = "YES"
            continue
        slack = limit-abs(r1-r2)-abs(c1-c2)
        if slack < 0:
            continue

        a = 2*(c1*N+r1)
        b = 2*(c2*N+r2)
        tile = tiles[b//2]
        other = b+1
        if tile == 2:
            b = other
        elif tile == 1:
            other = b

        lo,hi = min(c1,c2),max(c1,c2)
        extra = slack//2
        queries.append((lo, hi, lo-extra, hi+extra-1, a, b, other, limit, i))

    dist = [-1]*len(graph)

    def bfs(source):
        dist[source] = 0
        queue = [source]
        for u in queue:
            step = dist[u]+1
            for v in graph[u]:
                if dist[v] == -1:
                    dist[v] = step
                    queue.append(v)

    def search(left, right, batch):
        if not batch:
            return

        begin = left*stride
        stop = (right+1)*stride
        blank = [-1]*(stop-begin)

        if left == right:
            by_start = {}
            for _,_,_,_,a,b,other,limit,i in batch:
                by_start.setdefault(a, []).append((b, other, limit, i))
            for a, group in by_start.items():
                dist[begin:stop] = blank
                bfs(a)
                for b,other,limit,i in group:
                    if 0 <= dist[b] <= limit or 0 <= dist[other] <= limit:
                        answer[i] = "YES"
            return

        mid = (left+right)//2
        crossing = cuts[mid]
        if crossing:
            pending = []
            for query in batch:
                if query[0] <= mid < query[1]:
                    pending.append(query)
            for source, _ in crossing:
                if not pending:
                    break
                dist[begin:stop] = blank
                bfs(source)
                still_no = []

                for query in pending:
                    _,_,_,_,a,b,other,limit,i = query
                    first = dist[a]
                    if first >= 0:
                        left_over = limit-first
                        if 0 <= dist[b] <= left_over or 0 <= dist[other] <= left_over:
                            answer[i] = "YES"
                            continue
                    still_no.append(query)
                pending = still_no
            for u,v in crossing:
                graph[u].remove(v)
                graph[v].remove(u)
        before, after = [], []
        for query in batch:
            if answer[query[-1]] == "NO":
                if query[1] <= mid:
                    before.append(query)
                elif query[0] > mid:
                    after.append(query)

        search(left, mid, before)
        search(mid+1, right, after)

    search(0, M-1, queries)
    return answer
def main():
    read = sys.stdin.readline
    T = int(read())
    output = []
    for _ in range(T):
        N,M,Q = map(int, read().split())
        G = [read().strip() for _ in range(N)]
        start,end,K = [],[],[]
        for _ in range(Q):
            r1,c1,r2,c2,k = map(int, read().split())
            start.append((r1,c1))
            end.append((r2,c2))
            K.append(k)
        output.extend(solve(N,M,Q,G,start,end,K))
    sys.stdout.write("\n".join(output)+"\n")



if __name__ == "__main__":
    main()