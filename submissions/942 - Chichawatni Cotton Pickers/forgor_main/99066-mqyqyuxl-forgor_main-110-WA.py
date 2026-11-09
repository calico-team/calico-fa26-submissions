import sys

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
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
            A[0] = 0
        else:
            A[i - 1] = parent[i]
            
    return A

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
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
    seen = [False] * (N + 1)
    for i in range(2, N + 1):
        if i != missing_node and parent[i] > 0:
            edges.append((parent[i], i))
            seen[i] = True
            seen[parent[i]] = True
            
    if missing_node != -1:
        target = 1 if missing_node != 1 else 2
        edges.append((target, missing_node))
        seen[missing_node] = True
        
    while len(edges) < N - 1:
        for node in range(1, N + 1):
            if not seen[node]:
                edges.append((1, node))
                seen[node] = True
                break
                
    return edges

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    phase = input_data[0]
    N = int(input_data[1])
    
    if phase == 'FIRST':
        E = []
        idx = 2
        for _ in range(N - 1):
            u = int(input_data[idx])
            v = int(input_data[idx+1])
            E.append((u, v))
            idx += 2
        A = solve_phase1(N, E)
        print(' '.join(map(str, A)))
    else:
        A = [int(x) for x in input_data[2:]]
        edges = solve_phase2(N, A)
        for u, v in edges:
            print(f"{u} {v}")

if __name__ == '__main__':
    main()
