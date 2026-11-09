import sys


def encode(n, edges):
    """Return the Pruefer sequence (values 1..n) of a tree on vertices 1..n."""
    deg = [0] * n
    nx = [0] * n  # xor of neighbours
    for u, v in edges:
        u -= 1
        v -= 1
        deg[u] += 1
        deg[v] += 1
        nx[u] ^= v
        nx[v] ^= u
    seq = []
    if n <= 2:
        return seq
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    for _ in range(n - 2):
        v = nx[leaf]
        seq.append(v + 1)
        deg[v] -= 1
        nx[v] ^= leaf
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    return seq


def decode(n, seq):
    """Rebuild the edge list (1-indexed) from a Pruefer sequence."""
    deg = [1] * n
    for v in seq:
        deg[v - 1] += 1
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    edges = []
    for v1 in seq:
        v = v1 - 1
        edges.append((leaf + 1, v1))
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    edges.append((leaf + 1, n))
    return edges


def phase1(n, edges):
    seq = encode(n, edges)
    x = 0
    for v in seq:
        x ^= v
    return seq + [x, 0]


def phase2(n, a):
    seq = a[:n - 2]
    par = a[n - 2]
    if -1 in seq:
        i = seq.index(-1)
        x = par
        for j, v in enumerate(seq):
            if j != i:
                x ^= v
        seq[i] = x
    return decode(n, seq)


def run(tokens):
    mode = tokens[0]
    n = int(tokens[1])
    out = []
    if mode == "FIRST":
        edges = [(int(tokens[2 + 2 * i]), int(tokens[3 + 2 * i])) for i in range(n - 1)]
        out.append(" ".join(map(str, phase1(n, edges))))
    else:
        a = [int(t) for t in tokens[2:2 + n]]
        for u, v in sorted(tuple(sorted(e)) for e in phase2(n, a)):
            out.append(f"{u} {v}")
    return "\n".join(out)


def main():
    try:
        tokens = sys.stdin.read().split()
    except Exception:
        tokens = []
    if tokens:
        print(run(tokens))
        return
    # Notebook demo: sample interaction
    print("Phase 1 output:")
    p1 = run("FIRST 3 1 2 1 3".split())
    print(p1)
    a = p1.split()
    a[0] = "-1"
    print("Phase 2 output (first value erased):")
    print(run(["SECOND", "3"] + a))


main()