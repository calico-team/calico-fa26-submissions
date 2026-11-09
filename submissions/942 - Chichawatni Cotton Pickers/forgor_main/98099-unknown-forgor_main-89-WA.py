import sys

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Produce a list of N integers A_1 .. A_N representing the tree.
    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # A robust way to encode the tree is to store the two endpoints of each edge 
    # in an array of size 2N - 2, or encode the adjacency list / parent pointers.
    # Since Phase 1 outputs N integers A_1 .. A_N, let's encode the parent of each node 
    # 1 to N, but encode it with a checksum or direct adjacency mapping.
    # Even simpler: root the tree at 1. For each node i from 1 to N, store its parent P[i] (P[1] = 0).
    # To prevent ambiguity when one value is -1, we can also store the total degree or edge count.
    
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        
    parent = [0] * (N + 1)
    visited = [False] * (N + 1)
    stack = [1]
    visited[1] = True
    
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if not visited[v]:
                visited[v] = True
                parent[v] = u
                stack.append(v)
                
    A = [0] * N
    for i in range(1, N + 1):
        if i == 1:
            A[i - 1] = 0
        else:
            A[i - 1] = parent[i]
            
    return A

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    The N - 1 edges of the original tree as (u, v) pairs
    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    parent = [0] * (N + 1)
    missing_node = -1
    
    for i in range(1, N + 1):
        val = A[i - 1]
        if val == -1:
            missing_node = i
        else:
            parent[i] = val
            
    parent[1] = 0
    
    edges = []
    for i in range(2, N + 1):
        if i != missing_node:
            edges.append((parent[i], i))
            
    if missing_node != -1:
        # Find which node in 1..N (other than missing_node) is not connected or can be its parent.
        # To guarantee a valid tree of N-1 edges without cycles, missing_node can connect to node 1 
        # (or any node that doesn't create a cycle). Since exactly one parent is missing, 
        # connecting missing_node to node 1 (if missing_node != 1) always forms a valid spanning tree 
        # as long as 1 is in the main component.
        target = 1 if missing_node != 1 else 2
        edges.append((target, missing_node))
                
    return edges

def main():
    phase_line = sys.stdin.readline()
    if not phase_line:
        return
    phase = phase_line.strip()
    
    N_line = sys.stdin.readline()
    if not N_line:
        return
    N = int(N_line.strip())
    
    if phase == 'FIRST':
        E = []
        for _ in range(N - 1):
            parts = sys.stdin.readline().split()
            u = int(parts[0])
            v = int(parts[1])
            E.append((u, v))
        A = solve_phase1(N, E)
        print(' '.join(map(str, A)))
    else:
        A = list(map(int, sys.stdin.readline().split()))
        edges = solve_phase2(N, A)
        for u, v in edges:
            print(f"{u} {v}")

if __name__ == '__main__':
    main()
