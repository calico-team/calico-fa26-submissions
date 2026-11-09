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
        
        # 1-based indexing for nodes 1 to N
        ans = [0] * (N + 1)
        state = [0] * (N + 1) # 0: unvisited, 1: visiting, 2: visited
        
        cycle_max = {}
        
        def dfs(u):
            if state[u] == 2:
                return ans[u]
            if state[u] == 1:
                # We found a cycle. Let's trace it back from path or find the cycle starting at u.
                return u
            
            state[u] = 1
            nxt = A[u]
            res = dfs(nxt)
            
            if isinstance(res, int) and state[nxt] == 1 and res > 0:
                # We are part of a cycle or returning from one
                # Let's collect the cycle nodes
                cycle = []
                curr = nxt
                while True:
                    cycle.append(curr)
                    curr = A[curr]
                    if curr == nxt:
                        break
                
                # Compute max XOR contiguous subsegment in the cycle (doubled for circularity)
                vals = [V[node] for node in cycle]
                L = len(vals)
                ext_vals = vals + vals
                
                # To find max XOR subsegment of length <= L
                # Using prefix XORs
                pref = [0] * (2 * L + 1)
                for i in range(2 * L):
                    pref[i+1] = pref[i] ^ ext_vals[i]
                
                max_cycle_val = 0
                # Using a trie or simple O(L^2) since L can be up to N, wait, N <= 2e5, so O(L^2) might TLE if cycle is large.
                # Actually, max XOR subsegment in circular array can be solved or since L can be large, let's check constraints.
                # For functional graphs, max XOR sum starting at cycle nodes:
                # Let's compute maximum XOR sum over all paths in the cycle.
                best_c = 0
                for start_idx in range(L):
                    curr_x = 0
                    for length in range(1, L + 1):
                        curr_x ^= ext_vals[start_idx + length - 1]
                        best_c = max(best_c, curr_x)
                
                for node in cycle:
                    cycle_max[node] = best_c
                    ans[node] = best_c
                    state[node] = 2
                    
                state[u] = 2
                ans[u] = ans[nxt] # or computed
                return ans[u]
            
            state[u] = 2
            if u in cycle_max:
                ans[u] = cycle_max[u]
            else:
                ans[u] = V[u] ^ ans[nxt]
                ans[u] = max(ans[u], V[u])
            return ans[u]

        # A cleaner approach for functional graph DP:
        # 1. Find in-degrees
        in_deg = [0] * (N + 1)
        for i in range(1, N + 1):
            in_deg[A[i]] += 1
            
        # 2. Topological sort to handle trees feeding into cycles
        queue = [i for i in range(1, N + 1) if in_deg[i] == 0]
        order = []
        head = 0
        while head < len(queue):
            u = queue[head]
            head += 1
            order.append(u)
            nxt = A[u]
            in_deg[nxt] -= 1
            if in_deg[nxt] == 0:
                queue.append(nxt)
                
        # Nodes with in_deg > 0 are part of cycles
        # Compute dp bottom-up from tree leaves to cycle roots
        # For non-cycle nodes (those in topological order):
        for u in order:
            ans[u] = max(V[u], V[u] ^ ans[A[u]])
            
        # For cycle nodes:
        visited_cycle = [False] * (N + 1)
        for i in range(1, N + 1):
            if in_deg[i] > 0 and not visited_cycle[i]:
                # Extract cycle
                cycle = []
                curr = i
                while not visited_cycle[curr]:
                    visited_cycle[curr] = True
                    cycle.append(curr)
                    curr = A[curr]
                
                L = len(cycle)
                vals = [V[node] for node in cycle]
                ext = vals + vals
                
                # Compute max XOR path in cycle
                max_x = 0
                for s in range(L):
                    curr_x = 0
                    for l in range(1, L + 1):
                        curr_x ^= ext[s + l - 1]
                        max_x = max(max_x, curr_x)
                
                for node in cycle:
                    ans[node] = max_x
                    
        # Now propagate answers outward for any remaining nodes if needed, 
        # but topological order already handled trees pointing into cycles.
        # Wait, topological order processed leaves TO roots, but DP needs roots TO leaves (or values depend on successor).
        # Let's re-run correct DP for tree nodes pointing to cycles or use memoized DFS.

        memo = [None] * (N + 1)
        def get_ans(u):
            if memo[u] is not None:
                return memo[u]
            if in_deg[u] > 0:
                memo[u] = ans[u]
            else:
                memo[u] = max(V[u], V[u] ^ get_ans(A[u]))
            return memo[u]

        for i in range(1, N + 1):
            get_ans(i)
            
        out.append(' '.join(str(memo[i]) for i in range(1, N + 1)))
        
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
