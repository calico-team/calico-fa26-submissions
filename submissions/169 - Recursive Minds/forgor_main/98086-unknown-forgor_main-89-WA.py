def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    edg = [[] for _ in range(N + 1)]
    for u, v in E:
        edg[u].append(v)
        edg[v].append(u)

    def dfs(u, p, d):
        depth[u] = d
        parent[u] = p
        xor[u] = u
        for v in edg[u]:
            if v != p:
                dfs(v, u, d + 1)
                xor[u] ^= xor[v]

    depth = [0] * (N + 1)
    parent = [0] * (N + 1)
    xor = [0] * (N + 1)
    
    root = 1
    dfs(root, 0, 0)
    
    A = [0] * N
    
    for i in range(1, N + 1):
        if i == root:
            A[i-1] = xor[root]
        else:
            A[i-1] = parent[i] * (N + 1) + xor[i]
            
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    miss = -1
    for i in range(N):
        if A[i] == -1:
            miss = i
            break
            
    node = miss + 1
    root = -1
    totalxor = 0
    for i in range(N):
        if i != miss:
            if A[i] <= N:
                root = i + 1
                total_xor = A[i]
                break
                
    if root == -1:
        root = node
        total_xor = 0
        for i in range(1, N + 1):
            total_xor ^= i
    if node == root:
        A[miss] = total_xor
    edges = []
    parent = [0] * (N + 1)
    xor = [0] * (N + 1)
    for i in range(N):
        if i + 1 != root and i != miss:
            parent[i+1] = A[i] // (N + 1)
            xor[i+1] = A[i] % (N + 1)
            
    if node != root:
        xor_sum = [0] * (N + 1)
        for i in range(1, N + 1):
            if i != root and i != node:
                p = parent[i]
                xor_sum[p] ^= xor[i]        
        miss_parent = -1
        for i in range(1, N + 1):
            if i != node:
                expect_xor = i ^ xor_sum[i]
                subtree_xor = total_xor if i == root else xor[i]
                
                if expect_xor != subtree_xor:
                    miss_parent = i
                    missing_subtree_xor = subtree_xor ^ expect_xor
                    parent[node] = miss_parent
                    xor[node] = missing_subtree_xor
                    break
    
    for i in range(1, N + 1):
        if i != root:
            edges.append((i, parent[i]))
            
    return edges


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
