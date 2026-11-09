import sys
import heapq


# A tree on vertices 0..n-1 is fully described by its Prufer sequence:
# a list of n-2 vertex labels. In phase 0 we output the Prufer sequence
# plus two checksums (all values kept below n). In phase 1 exactly one
# value is replaced by -1, but we can see *where* the hole is, so a
# single checksum modulo n is enough to recover a missing Prufer entry:
# the missing entry is the unique value in [0, n) matching the checksum.

def prufer_encode(n, adj):
    deg = [len(adj[v]) for v in range(n)]
    removed = [False] * n
    leaves = [v for v in range(n) if deg[v] == 1]
    heapq.heapify(leaves)
    seq = []
    for _ in range(n - 2):
        leaf = heapq.heappop(leaves)
        removed[leaf] = True
        nxt = None
        for u in adj[leaf]:
            if not removed[u]:
                nxt = u
                break
        seq.append(nxt)
        deg[nxt] -= 1
        if deg[nxt] == 1:
            heapq.heappush(leaves, nxt)
    return seq


def prufer_decode(n, seq):
    deg = [1] * n
    for x in seq:
        deg[x] += 1
    leaves = [v for v in range(n) if deg[v] == 1]
    heapq.heapify(leaves)
    edges = []
    for x in seq:
        leaf = heapq.heappop(leaves)
        edges.append((leaf, x))
        deg[leaf] -= 1
        deg[x] -= 1
        if deg[x] == 1:
            heapq.heappush(leaves, x)
    a = heapq.heappop(leaves)
    b = heapq.heappop(leaves)
    edges.append((a, b))
    return edges


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    phase = data[0]
    nums = list(map(int, data[1:]))

    if phase == "FIRST":
        n = nums[0]
        adj = [[] for _ in range(n)]
        vals = nums[1:]
        for i in range(n - 1):
            u, v = vals[2 * i], vals[2 * i + 1]
            adj[u].append(v)
            adj[v].append(u)
        if n == 1:
            print(0)
            return
        seq = prufer_encode(n, adj)
        s1 = sum(seq) % n
        s2 = sum((i + 1) * x for i, x in enumerate(seq)) % n
        out = seq + [s1, s2]
        print(" ".join(map(str, out)))
    else:  # SECOND
        n = nums[0]
        a = nums[1:1 + n]
        if n == 1:
            return
        seq = a[:n - 2]
        if -1 in seq:
            i = seq.index(-1)
            known = sum(x for x in seq if x != -1)
            seq[i] = (a[n - 2] - known) % n
        edges = prufer_decode(n, seq)
        print("\n".join(f"{u} {v}" for u, v in edges))


if __name__ == "__main__":
    solve()
