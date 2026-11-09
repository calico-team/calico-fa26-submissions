import sys

# Increase recursion depth for deep functional graphs
sys.setrecursionlimit(300000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    T = int(input_data[idx])
    idx += 1
    
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        idx += 1
        
        A = [0] + [int(x) for x in input_data[idx : idx + N]]
        idx += N
        V = [0] + [int(x) for x in input_data[idx : idx + N]]
        idx += N
        
        ans = [-1] * (N + 1)
        vis = [0] * (N + 1) # 0: unvisited, 1: visiting, 2: visited
        
        def dfs(u):
            if vis[u] == 2:
                return ans[u]
            if vis[u] == 1:
                # Found a cycle! Let's extract the cycle nodes
                cycle = []
                curr = u
                while True:
                    cycle.append(curr)
                    curr = A[curr]
                    if curr == u:
                        break
                
                L = len(cycle)
                vals = [V[node] for node in cycle]
                ext = vals + vals
                
                # For each node in the cycle, compute the max XOR subsegment starting at this node
                # Since we can stop at any point, we look at all subsegments starting from index i.
                cycle_ans = {}
                for i in range(L):
                    best = 0
                    curr_x = 0
                    for length in range(1, L + 1):
                        curr_x ^= ext[i + length - 1]
                        best = max(best, curr_x)
                    cycle_ans[cycle[i]] = best
                
                for node in cycle:
                    ans[node] = cycle_ans[node]
                    vis[node] = 2
                return ans[u]
            
            vis[u] = 1
            nxt = A[u]
            res = dfs(nxt)
            
            if vis[u] != 2:
                vis[u] = 2
                ans[u] = max(V[u], V[u] ^ ans[nxt])
            return ans[u]

        for i in range(1, N + 1):
            if vis[i] == 0:
                dfs(i)
                
        out.append(' '.join(str(ans[i]) for i in range(1, N + 1)))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
