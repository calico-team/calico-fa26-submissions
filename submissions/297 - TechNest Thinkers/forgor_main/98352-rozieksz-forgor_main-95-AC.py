import sys
import random


def encode(n, edges):
    
    if n == 2:
        return [0, 0]
    adj = [[] for _ in range(n)]
    deg = [0] * n
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1
    
    parent = [-1] * n
    seen = [False] * n
    seen[n - 1] = True
    stack = [n - 1]
    while stack:
        x = stack.pop()
        for y in adj[x]:
            if not seen[y]:
                seen[y] = True
                parent[y] = x
                stack.append(y)
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    code = []
    for _ in range(n - 2):
        nxt = parent[leaf]
        code.append(nxt + 1)         
        deg[nxt] -= 1
        if deg[nxt] == 1 and nxt < ptr:
            leaf = nxt
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    x = 0
    for c in code:
        x ^= c
    return code + [x, 0]


def decode(n, a):
   
    if n == 2:
        return [(1, 2)]
    code = a[:n - 2]
    for i in range(n - 2):
        if code[i] == -1:
            x = a[n - 2]
            for j in range(n - 2):
                if j != i:
                    x ^= code[j]
            code[i] = x
            break
    code = [c - 1 for c in code]      
    deg = [1] * n
    for v in code:
        deg[v] += 1
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    res = []
    for v in code:
        res.append((leaf + 1, v + 1))
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    res.append((leaf + 1, n))
    return res


def run(text):
    tok = text.split()
    phase = tok[0]
    n = int(tok[1])
    if phase == "FIRST":
        edges = []
        for i in range(n - 1):
            edges.append((int(tok[2 + 2 * i]) - 1, int(tok[3 + 2 * i]) - 1))
        return " ".join(map(str, encode(n, edges)))
    a = [int(x) for x in tok[2:2 + n]]
    return "\n".join("%d %d" % e for e in decode(n, a))


def self_test():
    
    for it in range(3000):
        n = random.randint(2, 12)
        edges = [(random.randint(1, i - 1), i) for i in range(2, n + 1)]
        perm = list(range(1, n + 1))
        random.shuffle(perm)
        edges = [(perm[u - 1], perm[v - 1]) for u, v in edges]
        out1 = run("FIRST\n%d\n" % n + "\n".join("%d %d" % e for e in edges))
        a = list(map(int, out1.split()))
        assert len(a) == n and all(0 <= x <= 10**6 for x in a)
        k = random.randrange(n)
        a[k] = -1
        out2 = run("SECOND\n%d\n%s" % (n, " ".join(map(str, a))))
        got = set(frozenset(map(int, l.split())) for l in out2.split("\n"))
        want = set(frozenset(e) for e in edges)
        assert got == want and len(got) == n - 1, (n, edges, a)
    print("OK, 3000 test pass")


if len(sys.argv) > 1 and sys.argv[1] == "test":
    self_test()
else:
    print(run(sys.stdin.read()))