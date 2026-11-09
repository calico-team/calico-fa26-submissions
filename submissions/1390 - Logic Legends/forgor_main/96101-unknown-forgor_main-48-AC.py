MOD = 1000001
 
 
def solve_phase1(N, E):
    adj = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1
    par = [0] * (N + 1)
    order = [N]
    par[N] = -1
    for u in order:
        for w in adj[u]:
            if w != par[u]:
                par[w] = u
                order.append(w)
    code = []
    if N > 2:
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
        for _ in range(N - 2):
            p = par[leaf]
            code.append(p)
            deg[p] -= 1
            if deg[p] == 1 and p < ptr:
                leaf = p
            else:
                ptr += 1
                while deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
    A = code + [sum(code) % MOD]
    while len(A) < N:
        A.append(0)
    return A
 
 
def solve_phase2(N, A):
    code_len = N - 2
    A = A[:]
    if -1 in A:
        pos = A.index(-1)
        if pos < code_len:
            others = sum(A[i] for i in range(code_len) if i != pos)
            A[pos] = (A[code_len] - others) % MOD
    code = A[:code_len]
    deg = [1] * (N + 1)
    for v in code:
        deg[v] += 1
    edges = []
    if N > 2:
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
        leaf = ptr
        for v in code:
            edges.append((leaf, v))
            deg[v] -= 1
            if deg[v] == 1 and v < ptr:
                leaf = v
            else:
                ptr += 1
                while deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
        edges.append((leaf, N))
    else:
        edges.append((1, 2))
    return edges
 
 
def main():
    phase = input().strip()
    N = int(input())
    if phase == 'FIRST':
        E = []
        for _ in range(N - 1):
            u, v = map(int, input().split())
            E.append((u, v))
        A = solve_phase1(N, E)
        print(' '.join(map(str, A)))
    else:
        A = list(map(int, input().split()))
        for u, v in solve_phase2(N, A):
            print(u, v)
 
 
if __name__ == '__main__':
    main()
 