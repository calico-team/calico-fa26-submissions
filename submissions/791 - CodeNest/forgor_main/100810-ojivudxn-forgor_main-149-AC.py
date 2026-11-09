import sys

def solve():
   
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    phase = input_data[0]
    n = int(input_data[1])
    
    if phase == "FIRST":
       
        adj = [[] for _ in range(n + 1)]
        idx = 2
        for _ in range(n - 1):
            u = int(input_data[idx])
            v = int(input_data[idx+1])
            idx += 2
            adj[u].append(v)
            adj[v].append(u)
            
        
        parent = [0] * (n + 1)
        q = [1]
        visited = [False] * (n + 1)
        visited[1] = True
        
       
        head = 0
        while head < len(q):
            u = q[head]
            head += 1
            for v in adj[u]:
                if not visited[v]:
                    visited[v] = True
                    parent[v] = u
                    q.append(v)
                    
        a = [0] * (n + 1)
        xor_sum = 0
        
        for i in range(2, n + 1):
            a[i] = parent[i]
            xor_sum ^= parent[i]
            
     
        a[1] = xor_sum
        
       
        print(*(a[1:]))
        
    else:

        a = [0] * (n + 1)
        missing_idx = -1
        
        for i in range(1, n + 1):
            a[i] = int(input_data[1 + i])
            if a[i] == -1:
                missing_idx = i
                
       
        if missing_idx > 1:
            xor_sum = a[1]
            for i in range(2, n + 1):
                if i != missing_idx:
                    xor_sum ^= a[i]
            a[missing_idx] = xor_sum
            
       
        out = []
        for i in range(2, n + 1):
            out.append(f"{i} {a[i]}")
            
        print('\n'.join(out))

if __name__ == '__main__':
    solve()