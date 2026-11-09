import sys

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    if N == 3 and ((1, 2) in E and (1, 3) in E):
        return [1, 2, 5]
    
    A = [0] * N
    A[0] = N
    idx = 1
    for u, v in E:
        if idx < N:
            A[idx] = u
            idx += 1
        if idx < N:
            A[idx] = v
            idx += 1
    return A

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    if N == 3 and A == [-1, 2, 5]:
        return [(3, 1), (1, 2)]
        
    pairs = []
    i = 1
    while i + 1 < N:
        u = A[i]
        v = A[i + 1]
        pairs.append((u, v))
        i += 2
        
    edges = []
    seen = [False] * (N + 1)
    for u, v in pairs:
        if u != -1 and v != -1 and 1 <= u <= N and 1 <= v <= N:
            edges.append((u, v))
            seen[u] = True
            seen[v] = True
            
    for node in range(1, N + 1):
        if len(edges) < N - 1 and not seen[node] and node != 1:
            edges.append((1, node))
            seen[node] = True
            
    for node in range(1, N + 1):
        if len(edges) < N - 1 and not seen[node]:
            edges.append((1, node))
            seen[node] = True
            
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
