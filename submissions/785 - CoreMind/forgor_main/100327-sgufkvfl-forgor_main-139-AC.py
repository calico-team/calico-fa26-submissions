import sys
from collections import deque


def phase_one(data):
    n = int(data[0])
    adj = [[] for _ in range(n + 1)]
    idx = 1
    for _ in range(n - 1):
        u = int(data[idx]); v = int(data[idx + 1]); idx += 2
        adj[u].append(v)
        adj[v].append(u)

    # Root the tree at vertex 1 and record each vertex's parent.
    parent = [0] * (n + 1)
    seen = [False] * (n + 1)
    seen[1] = True
    q = deque([1])
    while q:
        u = q.popleft()
        for w in adj[u]:
            if not seen[w]:
                seen[w] = True
                parent[w] = u
                q.append(w)

    # A_1 = XOR of all parents (a checksum, < 2^18 <= 10^6); A_i = parent of i.
    checksum = 0
    for i in range(2, n + 1):
        checksum ^= parent[i]
    out = [checksum] + parent[2:]
    sys.stdout.write(" ".join(map(str, out)) + "\n")


def phase_two(data):
    n = int(data[0])
    a = [int(x) for x in data[1:1 + n]]
    missing = a.index(-1)
    if missing != 0:
        # Recover the erased parent from the checksum.
        x = a[0]
        for i in range(1, n):
            if i != missing:
                x ^= a[i]
        a[missing] = x
    out = []
    for i in range(1, n):
        out.append(f"{i + 1} {a[i]}")
    sys.stdout.write("\n".join(out) + "\n")


def main():
    data = sys.stdin.buffer.read().split()
    phase = data[0].decode()
    if phase == "FIRST":
        phase_one(data[1:])
    else:
        phase_two(data[1:])


if __name__ == "__main__":
    main()
