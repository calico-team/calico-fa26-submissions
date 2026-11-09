import sys
def solve_phase1(N,E):
    graph = [[] for _ in range(N+1)]
    for u,v in E:
        graph[u].append(v)
        graph[v].append(u)
    parent = [0]*(N+1)
    stack = [1]
    while stack:
        u = stack.pop()
        for v in graph[u]:
            if v == parent[u]:
                continue
            parent[v] = u
            stack.append(v)
    ans = parent[2:]
    check = 0
    for x in ans:
        check ^= x
    ans.append(check)
    return ans

def solve_phase2(N,A):
    pos = A.index(-1)
    missing = 0
    for x in A:
        if x != -1:
            missing ^= x
    A[pos] = missing
    edges = []
    for v in range(2, N + 1):
        edges.append((v, A[v-2]))
    return edges

def main():
    input = sys.stdin.buffer.readline
    phase = input().strip()
    N = int(input())
    if phase == b"FIRST":
        E = []
        for _ in range(N-1):
            u,v = map(int,input().split())
            E.append((u,v))
        print(*solve_phase1(N,E))
    else:
        A = list(map(int,sys.stdin.buffer.read().split()))
        edges = solve_phase2(N,A)
        sys.stdout.write("\n".join(f"{u} {v}" for u,v in edges))
        sys.stdout.write("\n")

if __name__ == "__main__":
    main()