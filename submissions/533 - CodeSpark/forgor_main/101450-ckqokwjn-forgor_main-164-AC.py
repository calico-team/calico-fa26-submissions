import sys

MOD = 1000001  # values must stay in [0, 10^6]

def phase1(data, p):
    n = int(data[p]); p += 1
    if n == 2:
        print("0 0")
        return
    adj = [[] for _ in range(n)]
    deg = [0] * n
    for _ in range(n - 1):
        u = int(data[p]) - 1; v = int(data[p+1]) - 1; p += 2
        adj[u].append(v); adj[v].append(u)
        deg[u] += 1; deg[v] += 1
    parent = [-1] * n
    stack = [n - 1]
    seen = [False] * n
    seen[n - 1] = True
    while stack:
        x = stack.pop()
        for y in adj[x]:
            if not seen[y]:
                seen[y] = True
                parent[y] = x
                stack.append(y)
    code = []
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    for _ in range(n - 2):
        nx = parent[leaf]
        code.append(nx + 1)
        deg[nx] -= 1
        if deg[nx] == 1 and nx < ptr:
            leaf = nx
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    s = sum(code) % MOD
    code.append(s)
    code.append(0)
    print(" ".join(map(str, code)))

def phase2(data, p):
    n = int(data[p]); p += 1
    a = [int(x) for x in data[p:p+n]]
    if n == 2:
        print("1 2")
        return
    k = n - 2
    idx = -1
    for i in range(n):
        if a[i] == -1:
            idx = i
            break
    code = a[:k]
    if 0 <= idx < k:
        s = a[k]
        others = sum(code) + 1
        code[idx] = (s - others) % MOD
    code = [c - 1 for c in code]
    deg = [1] * n
    for v in code:
        deg[v] += 1
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    out = []
    for v in code:
        out.append("%d %d" % (leaf + 1, v + 1))
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    out.append("%d %d" % (leaf + 1, n))
    print("\n".join(out))

def main():
    data = sys.stdin.read().split()
    if data[0] == "FIRST":
        phase1(data, 1)
    else:
        phase2(data, 1)

main()