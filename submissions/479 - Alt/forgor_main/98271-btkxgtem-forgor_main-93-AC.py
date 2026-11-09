import sys
from collections import deque

def parse_input():
    tokens = sys.stdin.read().split()
    if not tokens:
        return None, None, None
    
    it = iter(tokens)
    phase = next(it)
    n = int(next(it))
    
    if phase == "FIRST":
        edges = []
        for _ in range(n - 1):
            u = int(next(it))
            v = int(next(it))
            edges.append((u, v))
        return phase, n, edges
    
    arr = [int(next(it)) for _ in range(n)]
    return phase, n, arr

def solve():
    phase, n, data = parse_input()
    if phase is None:
        return
        
    if phase == "FIRST":
        edges = data
        if n == 2:
            print("0 0")
            return
            
        adj = [[] for _ in range(n + 1)]
        deg = [0] * (n + 1)
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
            deg[u] += 1
            deg[v] += 1
            
        parent = [0] * (n + 1)
        vis = [False] * (n + 1)
        q = deque([n])
        vis[n] = True
        
        while q:
            curr = q.popleft()
            for nxt in adj[curr]:
                if not vis[nxt]:
                    vis[nxt] = True
                    parent[nxt] = curr
                    q.append(nxt)
                    
        ptr = 1
        while deg[ptr] != 1:
            ptr += 1
            
        leaf = ptr
        prufer = []
        
        for _ in range(n - 2):
            nxt = parent[leaf]
            prufer.append(nxt)
            deg[nxt] -= 1
            
            if deg[nxt] == 1 and nxt < ptr:
                leaf = nxt
            else:
                ptr += 1
                while ptr <= n and deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
                
        res = [0] * n
        x_total = 0
        x_weighted = 0
        
        for i in range(n - 2):
            val = prufer[i]
            res[i] = val
            x_total ^= val
            x_weighted ^= (val ^ i)
            
        res[n - 2] = x_total
        res[n - 1] = x_weighted
        print(*(res))
        
    else:
        arr = data
        if n == 2:
            print("1 2")
            return
            
        prufer = arr[:n-2]
        missing_idx = arr.index(-1)
        
        if missing_idx < n - 2:
            known_xor = 0
            for i, val in enumerate(prufer):
                if i != missing_idx:
                    known_xor ^= val
            prufer[missing_idx] = arr[n - 2] ^ known_xor
            
        deg = [1] * (n + 1)
        for x in prufer:
            deg[x] += 1
            
        ptr = 1
        while ptr <= n and deg[ptr] != 1:
            ptr += 1
            
        leaf = ptr
        edges = []
        
        for x in prufer:
            edges.append((leaf, x))
            deg[leaf] -= 1
            deg[x] -= 1
            
            if deg[x] == 1 and x < ptr:
                leaf = x
            else:
                ptr += 1
                while ptr <= n and deg[ptr] != 1:
                    ptr += 1
                leaf = ptr
                
        for i in range(1, n + 1):
            if deg[i] == 1:
                for j in range(i + 1, n + 1):
                    if deg[j] == 1:
                        edges.append((i, j))
                        break
                break
                
        for u, v in edges:
            print(f"{u} {v}")

if __name__ == '__main__':
    solve()
