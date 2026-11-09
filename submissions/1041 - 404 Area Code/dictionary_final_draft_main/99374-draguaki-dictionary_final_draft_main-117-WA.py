import sys
sys.setrecursionlimit(300000)
def solve():
    input_data = read_your_input()
    if not input_data:
        return  
    iterator = iter(input_data)
    try:
        T_str = next(iterator)
    except StopIteration:
        return
    T = int(T_str)
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        
   
        A = [0] + [int(next(iterator)) for _ in range(N)]
        V = [0] + [int(next(iterator)) for _ in range(N)]
        

        in_degree = [0] * (N + 1)
        for i in range(1, N + 1):
            in_degree[A[i]] += 1
          
        visited = [False] * (N + 1)
        dinosauraus = [i for i in range(1, N + 1) if in_degree[i] == 0]
        
        head = 0
        while head < len(dinosauraus):
            curr = dinosauraus[head]
            head += 1
            visited[curr] = True
            nxt = A[curr]
            in_degree[nxt] -= 1
            if in_degree[nxt] == 0:
                dinosauraus.append(nxt)
                
     
        max_in_cycle = {}
        for i in range(1, N + 1):
            if not visited[i]:
                cycle = []
                curr = i
                while not visited[curr]:
                    visited[curr] = True
                    cycle.append(curr)
                    curr = A[curr]
                    
                L = len(cycle)
                pref = [0] * (2 * L + 1)
                for idx in range(2 * L):
                    pref[idx + 1] = pref[idx] ^ V[cycle[idx % L]]
                    
               
                cycle_max = {}
                for start_idx in range(L):
                    node = cycle[start_idx]
                    best_xor = 0
                    current_accumulated = 0
                    for steps in range(1, L + 1):
                        current_accumulated ^= V[cycle[(start_idx + steps - 1) % L]]
                        if current_accumulated > best_xor:
                            best_xor = current_accumulated
                    cycle_max[node] = best_xor
                    
                max_in_cycle.update(cycle_max)
                
      
        ans = [0] * (N + 1)
        memo_visited = [False] * (N + 1)
        
        def compute_tree_node(node):
            if node in max_in_cycle:
                return max_in_cycle[node]
            if memo_visited[node]:
                return ans[node]
                
            nxt = A[node]
            nxt_max = compute_tree_node(nxt)
            
        
            ans[node] = max(V[node], V[node] ^ nxt_max)
            memo_visited[node] = True
            return ans[node]
            
        for i in range(1, N + 1):
            compute_tree_node(i)
            
        case_result = [str(ans[i]) for i in range(1, N + 1)]
        out.append(" ".join(case_result))
        
    print("\n".join(out))

def read_your_input():
    return sys.stdin.read().split()

if __name__ == "__main__":
    solve()
