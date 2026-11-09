import sys

def solve_phase1(n, e):
    adj = [[] for i in range(n + 1)]
    for u, v in e:
        adj[u].append(v)
        adj[v].append(u)
    
    parent = [0] * (n + 1)
    queue = [1]
    visited = [False] * (n + 1)
    visited[1] = True
    
    idx = 0
    while idx < len(queue):
        u = queue[idx]
        idx += 1
        for v in adj[u]:
            if not visited[v]:
                visited[v] = True
                parent[v] = u
                queue.append(v)
                
    a = [0] * n
    for i in range(1, n + 1):
        p = parent[i]
        val = p if p != 0 else i
        a[i - 1] = val + 1
    return a

def solve_phase2(n, a):
    edges = []
    for i in range(n):
        node = i + 1
        p = a[i]
        if p != -1 and p != node:
            edges.append((p, node))
    return edges

def main():
    phase = input().strip()
    n = int(input().strip())
    if phase == 'FIRST':
        e = []
        for i in range(n - 1):
            u, v = map(int, input().split())
            e.append((u, v))
        a = solve_phase1(n, e)
        print(' '.join(map(str, a)))
    else:
        a = list(map(int, input().split()))
        edges = solve_phase2(n, a)
        for u, v in edges:
            print(f"{u} {v}")

if __name__ == '__main__':
    main()