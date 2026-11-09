import sys

def read_your_input():
    input_data = sys.stdin.read().split()
    return input_data

def amnesiac():
    tokens = read_your_input()
    if not tokens:
        return
    
    phase = tokens[0]
    
    if phase == "FIRST":
        N = int(tokens[1])
        adj = [[] for _ in range(N + 1)]
        idx = 2
        for _ in range(N - 1):
            u = int(tokens[idx])
            v = int(tokens[idx + 1])
            idx += 2
            adj[u].append(v)
            adj[v].append(u)
        
        parent = [0] * (N + 1)
        stack = [1]
        visited = [False] * (N + 1)
        visited[1] = True
        
        while stack:
            curr = stack.pop()
            for nxt in adj[curr]:
                if not visited[nxt]:
                    visited[nxt] = True
                    parent[nxt] = curr
                    stack.append(nxt)
        
        A = [0] * (N + 1)
        xor_sum = 0
        for i in range(2, N + 1):
            A[i] = parent[i]
            xor_sum ^= A[i]
        
        A[1] = xor_sum
        
        print(*(A[1:]))

    elif phase == "SECOND":
        N = int(tokens[1])
        A = [int(x) for x in tokens[2:2 + N]]
        
        xor_sum = 0
        missing_idx = -1
        for i in range(N):
            if A[i] == -1:
                missing_idx = i
            else:
                xor_sum ^= A[i]
        
        A[missing_idx] = xor_sum
        
        edges = []
        for v in range(2, N + 1):
            edges.append(f"{v} {A[v - 1]}")
            
        print("\n".join(edges))


if __name__ == "__main__":
    amnesiac()