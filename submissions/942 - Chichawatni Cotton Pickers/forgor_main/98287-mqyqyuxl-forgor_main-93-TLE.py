import sys

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Produce a list of N integers A_1 .. A_N representing the tree.
    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
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
    """
    The N - 1 edges of the original tree as (u, v) pairs
    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    pairs = []
    i = 1
    while i + 1 < N:
        u = A[i]
        v = A[i + 1]
        pairs.append((u, v))
        i += 2
        
    edges = []
    seen_nodes = set()
    for u, v in pairs:
        if u != -1 and v != -1:
            edges.append((u, v))
            seen_nodes.add(u)
            seen_nodes.add(v)
            
    while len(edges) < N - 1:
        missing_node = -1
        for node in range(1, N + 1):
            if node not in seen_nodes:
                missing_node = node
                break
        if missing_node != -1:
            edges.append((1, missing_node))
            seen_nodes.add(missing_node)
        else:
            break
            
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
