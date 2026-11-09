import sys
import heapq

def enc(N, es):
    if N == 2:
        return [0, 0]

    adj = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    for u, v in es:
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1

    gone = [False] * (N + 1)
    h = [v for v in range(1, N + 1) if deg[v] == 1]
    heapq.heapify(h)

    seq = []
    for _ in range(N - 2):
        leaf = heapq.heappop(h)
        gone[leaf] = True
        for nb in adj[leaf]:
            if not gone[nb]:
                seq.append(nb)
                deg[nb] -= 1
                if deg[nb] == 1:
                    heapq.heappush(h, nb)
                break

    ck = sum(seq) % (N + 1)
    return seq + [ck, 0]

def dec(N, A):
    if N == 2:
        return [(1, 2)]

    j = A.index(-1)
    seq = A[:N - 2]
    if j < N - 2:
        # checksum fixes the one value that got eaten
        known = sum(seq[k] for k in range(N - 2) if k != j)
        seq[j] = (A[N - 2] - known) % (N + 1)

    deg = [1] * (N + 1)
    deg[0] = 0
    for v in seq:
        deg[v] += 1

    h = [v for v in range(1, N + 1) if deg[v] == 1]
    heapq.heapify(h)

    es = []
    for v in seq:
        leaf = heapq.heappop(h)
        es.append((leaf, v))
        deg[v] -= 1
        if deg[v] == 1:
            heapq.heappush(h, v)

    a = heapq.heappop(h)
    b = heapq.heappop(h)
    es.append((a, b))
    return es

def main():
    d = sys.stdin.read().split()
    ph = d[0]
    p = 1
    N = int(d[p]); p += 1

    if ph == "FIRST":
        es = []
        for _ in range(N - 1):
            u = int(d[p]); v = int(d[p+1]); p += 2
            es.append((u, v))
        print(" ".join(map(str, enc(N, es))))
    else:
        A = [int(d[p + i]) for i in range(N)]
        es = dec(N, A)
        sys.stdout.write("\n".join(f"{u} {v}" for u, v in es))

if __name__ == "__main__":
    main()