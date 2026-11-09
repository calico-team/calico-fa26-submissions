from collections import deque
def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE.
    adj = [[] for _ in range(N+1)]
    for u,v in E:
            adj[u].append(v)
            adj[v].append(u)
    
    parent = [0]*(N+1)
    visited = [False] * (N+1)
    queue= deque([1])
    visited[1] = True

    while queue:
        curr = queue.popleft()
        for next  in adj[curr]:
            if not visited[next]:
                visited[next] = True
                parent[next] = curr
                queue.append(next)
    


    xor_sum =0
    for i in range(2, N+1):
        xor_sum ^= parent[i]

    A = [0]*N
    A[0] = xor_sum
    for i in range(2,N+1):
        A[i-1]  = parent[i]
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    missing_index = -1
    for i in range(N):
        if A[i] == -1:
            missing_index = i
            break

    if missing_index >0:
        recovered = A[0]
        for i in range(1, N):
            if i !=missing_index:
                recovered ^= A[i]

        A[missing_index] = recovered

    edges =[]
    for i in range(1,N):
        vertex = i+1
        par =A[i]
        edges.append((vertex,par))

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
