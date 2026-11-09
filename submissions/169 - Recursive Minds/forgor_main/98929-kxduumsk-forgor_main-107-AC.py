from re import A
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

    parent = [0] * (N + 1)
    
    queue = [1]
    visited = [False] * (N + 1)
    visited[1] = True
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        for v in edg[u]:
            if not visited[v]:
                visited[v] = True
                parent[v] = u
                queue.append(v)


    A = [0] * N
    checksum = 0
    for i in range(2, N + 1):
        A[i-1] = parent[i]
        checksum ^= parent[i]
    A[0] = checksum
            
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    edges = []
    
    if A[0] == -1:
        for i in range(1, N):
            edges.append((i + 1, A[i]))
    else:
        miss = -1
        xor = 0
        for i in range(1, N):
            if A[i] == -1:
                miss = i
            else:
                xor ^= A[i]
                edges.append((i + 1, A[i]))
                
        if miss != -1:
            missingp = A[0] ^ xor
            edges.append((miss + 1, missingp))
            
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
