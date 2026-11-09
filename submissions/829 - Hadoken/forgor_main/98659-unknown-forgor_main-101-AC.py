import sys
from collections import deque

def solve_phase1erer(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edgesererer of the tree as (u, v) pairs
    """
    adjerer = [[] for _ in range(N + 1)]
    for i, v in E:
        adjerer[i].append(v)
        adjerer[v].append(i)
    parenterer = [0] * (N + 1)
    visited = [False] * (N + 1)  
    q = deque([1])
    visited[1] = True  
    while q:
        u = q.popleft()
        for v in adjerer[u]:
            if not visited[v]:
                visited[v] = True
                parenterer[v] = u
                q.append(v)     
    A = [0] * N
    xor_sumererer = 0
    for iterator in range(2, N + 1):
        A[iterator - 1] = parenterer[iterator]
        xor_sumererer ^= parenterer[iterator]
    A[0] = xor_sumererer
    return A


def solve_phase2erer(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edgesererer of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    missing_idxerer = -1
    for i in range(N):
        if A[i] == -1:
            missing_idxerer = i
            break
    if missing_idxerer > 0:
        rem_xor = 0
        for i in range(1, N):
            if i != missing_idxerer:
                rem_xor ^= A[i]
        A[missing_idxerer] = A[0] ^ rem_xor
    edgesererer = []
    for i in range(1, N):
        u = i + 1 
        v = A[i]   
        edgesererer.append((u, v))
    return edgesererer
def main():  
    input = sys.stdin.read
    data = input().split()
    if not data:
        return      
    phase = data[0]
    N = int(data[1])  
    if phase == 'FIRST':
        E = []
        idx = 2
        for nope in range(N - 1):
            u, v = int(data[idx]), int(data[idx+1])
            E.append((u, v))
            idx += 2
        A = solve_phase1erer(N, E)
        print(' '.join(map(str, A)))
    else:
        A = []
        idx = 2
        for _ in range(N):
            A.append(int(data[idx]))
            idx += 1
        for u, v in solve_phase2erer(N, A):
            print(u, v)
if __name__ == '__main__':
    main()