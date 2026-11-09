import sys


def amnesiac(tokens):
    pos = 0
    phase = tokens[pos]; pos += 1
    N = int(tokens[pos]); pos += 1
    if phase == "FIRST":
        adj = [[] for _ in range(N + 1)]
        for _ in range(N - 1):
            u = int(tokens[pos]); v = int(tokens[pos + 1]); pos += 2
            adj[u].append(v)
            adj[v].append(u)
        parent = [0] * (N + 1)
        seen = [False] * (N + 1)
        seen[N] = True
        stack = [N]
        while stack:
            u = stack.pop()
            for w in adj[u]:
                if not seen[w]:
                    seen[w] = True
                    parent[w] = u
                    stack.append(w)
        deg = [len(adj[i]) for i in range(N + 1)]
        seq = []
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
        for _ in range(N - 2):
            p = parent[leaf]
            seq.append(p)
            deg[p] -= 1
            if deg[p] == 1 and p < ptr:
                leaf = p
            else:
                ptr += 1
                while deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
        par = 0
        for x in seq:
            par ^= x
        res = seq + [par, par]
        print(" ".join(map(str, res)))
    else:
        A = [int(tokens[pos + i]) for i in range(N)]
        seq = A[:N - 2]
        par = A[N - 2] if A[N - 2] != -1 else A[N - 1]
        for i in range(N - 2):
            if seq[i] == -1:
                x = par
                for j in range(N - 2):
                    if j != i:
                        x ^= seq[j]
                seq[i] = x
                break
        deg = [1] * (N + 1)
        for x in seq:
            deg[x] += 1
        out = []
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
        for p in seq:
            out.append("%d %d" % (leaf, p))
            deg[p] -= 1
            if deg[p] == 1 and p < ptr:
                leaf = p
            else:
                ptr += 1
                while deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
        out.append("%d %d" % (leaf, N))
        print("\n".join(out))


def read_your_input():
    tokens = sys.stdin.read().split()
    amnesiac(tokens)


if __name__ == "__main__":
    read_your_input()