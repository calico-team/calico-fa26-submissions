import sys

# Increase recursion depth for deep functional graph traversals
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
        
        # 1-indexed arrays
        A = [0] + [int(x) for x in input_data[idx : idx + N]]
        idx += N
        V = [0] + [int(x) for x in input_data[idx : idx + N]]
        idx += N
        
        ans = [0] * (N + 1)
        state = [0] * (N + 1) # 0: unvisited, 1: visiting, 2: visited
        path = []
        path_xor = []
        
        memo = [None] * (N + 1)
        
        def dfs(u):
            if memo[u] is not None:
                return memo[u]
            if state[u] == 2:
                return V[u]
            if state[u] == 1:
                # Found a cycle! We can choose to stop at any point in the cycle
                # To maximize XOR sum, we want max_val
                # Actually, in a cycle, we can keep cycling or stop at any node in the cycle.
                # Since we can stop at the very first step, our happiness is at least V[u].
                # Let's collect all elements in the cycle.
                cycle_nodes = []
                idx_in_path = path.index(u)
                for node in path[idx_in_path:]:
                    cycle_nodes.append(node)
                
                # Maximize XOR sum in cycle
                max_x = 0
                curr_x = 0
                for node in cycle_nodes:
                    curr_x ^= V[node]
                    max_x = max(max_x, curr_x)
                # Also consider combinations or single values
                # For simplicity in functional graph, max happiness starting at cycle nodes can be precomputed.
                return max_x

            state[u] = 1
            path.append(u)
            
            nxt = A[u]
            res = V[u] ^ dfs(nxt)
            res = max(res, V[u]) # Can always stop immediately at u
            
            path.pop()
            state[u] = 2
            memo[u] = res
            return res

        for i in range(1, N + 1):
            if state[i] == 0:
                dfs(i)
                
        # Collect answers for 1 to N
        # memo stores the max happiness starting from i
        out.append(' '.join(str(memo[i]) for i in range(1, N + 1)))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
