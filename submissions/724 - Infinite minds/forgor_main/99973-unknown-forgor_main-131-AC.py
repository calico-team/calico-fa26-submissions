def encode(N,E):
    adj = [[] for _ in range(N+1)]
    deg = [0]*(N+2)
    for u,v in E:
        adj[u].append(v)
        adj[v].append(u)
        deg[u]+=1
        deg[v]+=1
    parent = [0]*(N+1)
    parent[N] = -1
    stack = [N]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if v!= parent[u]:
                parent[v] = u
                stack.append(v)
    code = []
    ptr = 1
    while deg[ptr]!=1:
        ptr+=1
    leaf = ptr
    for _ in range(N-2):
        v = parent[leaf]
        code.append(v)
        deg[v]-=1
        if deg[v]==1 and v<ptr:
            leaf = v
        else:
            ptr+=1
            while deg[ptr]!=1:
                ptr+=1
            leaf = ptr
    return code


def decode(N, code):
    deg = [1]*(N+2)
    for v in code:
        deg[v]+=1
    ptr = 1
    edges = []
    while deg[ptr]!=1:
        ptr+=1
    leaf = ptr
    for v in code:
        edges.append((leaf, v))
        deg[v]-=1
        if deg[v]==1 and v<ptr:
            leaf = v
        else:
            ptr+=1
            while deg[ptr]!=1:
                ptr+=1
            leaf = ptr
 
    edges.append((leaf, N))
    return edges





def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    if N == 2:
        return [0,0]
    code = encode(N,E)
    x = 0
    for v in code:
        x ^= v
    return code + [x, 0]
   






def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    if N == 2:
        return [(1, 2)]
    idx = A.index(-1)
    code = A[:N -2]
    if idx < N - 2:
        x = A[N-2]
        for i in range(N-2):
            if i != idx:
                x ^= code[i]
        code[idx] = x
    return decode(N, code)

def main():
    phase = input()
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
