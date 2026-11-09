import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    phase = input_data[0]
    n = int(input_data[1])
    
    if phase == "FIRST":
        edges = []
        idx = 2
        for _ in range(n - 1):
            u = int(input_data[idx])
            v = int(input_data[idx+1])
            edges.append((u, v))
            idx += 2
            
        adj = [[] for _ in range(n + 1)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
            
        parent = [0] * (n + 1)
        visited = [False] * (n + 1)
        queue = [1]
        visited[1] = True
        head = 0
        while head < len(queue):
            u = queue[head]
            head += 1
            for v in adj[u]:
                if not visited[v]:
                    visited[v] = True
                    parent[v] = u
                    queue.append(v)
                    
        r = [0] * (n + 1)
        xp = 0
        for i in range(1, n + 1):
            xp ^= parent[i]
            
        xr_prime = 0
        for i in range(1, n):
            r[i] = i % 4
            xr_prime ^= r[i]
            
        r[n] = xr_prime ^ (xp >> 18)
        
        a = []
        for i in range(1, n + 1):
            val = parent[i] + (r[i] << 18)
            a.append(str(val))
            
        print(" ".join(a))
        
    elif phase == "SECOND":
        a = []
        idx = 2
        for _ in range(n):
            a.append(int(input_data[idx]))
            idx += 1
            
        missing_idx = -1
        xor_sum = 0
        for i in range(n):
            if a[i] == -1:
                missing_idx = i
            else:
                xor_sum ^= a[i]
                
        a[missing_idx] = xor_sum
        
        for i in range(n):
            node_id = i + 1
            p = a[i] & 262143
            if node_id != 1:
                print(f"{node_id} {p}")

if __name__ == "__main__":
    solve()