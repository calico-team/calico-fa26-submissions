import sys

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Produce a list of N integers A_1 .. A_N representing the tree.
    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
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
                
    # A[i-1] = parent of node i. For node 1, parent is 0.
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
    missing_idx = -1
    
    for i in range(1, N + 1):
        val = A[i - 1]
        if val == -1:
            missing_idx = i  # node i lost its parent
        else:
            parent[i] = val
            
    parent[1] = 0
    
    edges = []
    for i in range(2, N + 1):
        if i != missing_idx:
            edges.append((parent[i], i))
            
    if missing_idx != -1:
        # We need to find the correct parent for missing_idx.
        # Since exactly one parent is missing, the nodes are partitioned into two components:
        # 1. The component containing node 1 (root).
        # 2. The component containing missing_idx.
        # To find which vertex p from the root component should connect to missing_idx, 
        # we can check which vertex can reach all nodes or use DSU/reachability.
        
        # Since N <= 200,000, we can find the component of missing_idx by following parent pointers upwards 
        # for all other nodes, or finding which node has no children/parent connection.
        # Actually, in a tree where one parent is missing, the missing_idx node is the root of a subtree 
        # whose parent edge was deleted. Its parent must be some node u in the rest of the tree.
        # Which node? Any node u that does not belong to the subtree of missing_idx!
        
        # Let's find all descendants of missing_idx using the present edges:
        children = [[] for _ in range(N + 1)]
        for child, p in enumerate(parent):
            if p > 0:
                children[p].append(child)
                
        # Find all nodes in the disconnected subtree rooted at missing_idx
        subtree_nodes = set()
        stack = [missing_idx]
        while stack:
            curr = stack.pop()
            subtree_nodes.add(curr)
            for nxt in children[curr]:
                stack.append(nxt)
                
        # The parent can be any node NOT in subtree_nodes (e.g., node 1 or its valid neighbor).
        # Connecting missing_idx to node 1 (or any valid node outside its subtree) always forms a valid tree!
        parent_candidate = 1
        if parent_candidate in subtree_nodes:
            # Find any node not in subtree_nodes
            for candidate in range(1, N + 1):
                if candidate not in subtree_nodes:
                    parent_candidate = candidate
                    break
                    
        edges.append((parent_candidate, missing_idx))
                
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
