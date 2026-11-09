from collections import deque

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
    
    parent = [0] * (N + 1)
    visited = [False] * (N + 1)
    
    queue = deque([1])
    visited[1] = True
    
    while queue:
        curr = queue.popleft()
        for nxt in adj[curr]:
            if not visited[nxt]:
                visited[nxt] = True
                parent[nxt] = curr
                queue.append(nxt)
                
    A = [0] * (N + 1)
    for i in range(2, N + 1):
        A[i] = parent[i]
        
    xor_sum = 0
    for i in range(2, N + 1):
        xor_sum ^= A[i]
    A[1] = xor_sum
    
    return A[1:]


def solve_phase2(N: int, A_list: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    A = [0] + A_list
    
    missing_idx = -1
    for i in range(1, N + 1):
        if A[i] == -1:
            missing_idx = i
            break
            
    if missing_idx != -1:
        xor_val = 0
        for i in range(1, N + 1):
            if i != missing_idx:
                xor_val ^= A[i]
        A[missing_idx] = xor_val
        
    edges = []
    for i in range(2, N + 1):
        edges.append((i, A[i]))
        
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