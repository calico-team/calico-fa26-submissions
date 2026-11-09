import sys
import heapq

def amnesiac():
    data = read_your_input()
    if not data:
        return
    phase = data[0]
    out_lines = []
    if phase == "FIRST":
        n = int(data[1])
        adj = [[] for _ in range(n + 1)]
        idx = 2
        for _ in range(n - 1):
            u = int(data[idx]); v = int(data[idx + 1]); idx += 2
            adj[u].append(v)
            adj[v].append(u)
        if n == 2:
            sys.stdout.write("0 0")
            return
        deg = [0] * (n + 1)
        for i in range(1, n + 1):
            deg[i] = len(adj[i])
        heap = [i for i in range(1, n + 1) if deg[i] == 1]
        heapq.heapify(heap)
        prufer = []
        for _ in range(n - 2):
            leaf = heapq.heappop(heap)
            # find its sole remaining neighbour
            nb = -1
            for w in adj[leaf]:
                if deg[w] > 0:
                    nb = w
                    break
            prufer.append(nb)
            deg[leaf] = 0
            deg[nb] -= 1
            if deg[nb] == 1:
                heapq.heappush(heap, nb)
        s_mod = sum(prufer) % (n + 1)
        A = prufer + [s_mod, 0]
        sys.stdout.write(" ".join(map(str, A)))
        return
    else:  # SECOND
        n = int(data[1])
        A = list(map(int, data[2:2 + n]))
        if n == 2:
            sys.stdout.write("1 2")
            return
        missing = -1
        for i, v in enumerate(A):
            if v == -1:
                missing = i
                break
        # parity is at n-2, dummy at n-1
        prufer = A[:n - 2]
        if missing != -1 and missing < n - 2:
            parity = A[n - 2]
            s_others = 0
            for i, v in enumerate(prufer):
                if i == missing:
                    continue
                s_others = (s_others + v) % (n + 1)
            rec = (parity - s_others) % (n + 1)
            # rec in 1..n for valid input; 0 would mean n+1, not possible
            if rec == 0:
                rec = n + 1
            prufer[missing] = rec
        # reconstruct tree from prufer
        deg = [1] * (n + 1)
        for v in prufer:
            deg[v] += 1
        heap = [i for i in range(1, n + 1) if deg[i] == 1]
        heapq.heapify(heap)
        edges = []
        for v in prufer:
            leaf = heapq.heappop(heap)
            edges.append((leaf, v))
            deg[leaf] -= 1
            deg[v] -= 1
            if deg[v] == 1:
                heapq.heappush(heap, v)
        l1 = heapq.heappop(heap)
        l2 = heapq.heappop(heap)
        edges.append((l1, l2))
        sys.stdout.write("\n".join(f"{u} {v}" for u, v in edges))
        return

def read_your_input():
    return sys.stdin.read().strip().split()

if __name__ == "__main__":
    amnesiac()