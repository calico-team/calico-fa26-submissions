import sys
from collections import deque

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    T = int(data[0])
    idx = 1
    
    out = []
    
    for _ in range(T):
        N = int(data[idx])
        idx += 1
        A = [0] + [int(x) for x in data[idx:idx+N]]
        idx += N
        V = [0] + [int(x) for x in data[idx:idx+N]]
        idx += N
        
        rev_adj = [[] for _ in range(N + 1)]
        for i in range(1, N + 1):
            rev_adj[A[i]].append(i)
            
        vis = [0] * (N + 1)
        ans = [0] * (N + 1)
        
        L_child = [0]
        R_child = [0]
        
        def new_node():
            L_child.append(0)
            R_child.append(0)
            return len(L_child) - 1
            
        def clone(node):
            L_child.append(L_child[node])
            R_child.append(R_child[node])
            return len(L_child) - 1
            
        def insert_val(root, val):
            node = clone(root) if root != 0 else new_node()
            curr = node
            for b in range(29, -1, -1):
                bit = (val >> b) & 1
                if bit == 0:
                    nxt = L_child[curr]
                    new_nxt = clone(nxt) if nxt != 0 else new_node()
                    L_child[curr] = new_nxt
                    curr = new_nxt
                else:
                    nxt = R_child[curr]
                    new_nxt = clone(nxt) if nxt != 0 else new_node()
                    R_child[curr] = new_nxt
                    curr = new_nxt
            return node
            
        def query_max(root, val):
            if root == 0:
                return 0
            curr = root
            best_s = 0
            for b in range(29, -1, -1):
                bit = (val >> b) & 1
                target = 1 - bit
                if target == 0 and L_child[curr] != 0:
                    curr = L_child[curr]
                    best_s |= (0 << b)
                elif target == 1 and R_child[curr] != 0:
                    curr = R_child[curr]
                    best_s |= (1 << b)
                else:
                    if bit == 0 and L_child[curr] != 0:
                        curr = L_child[curr]
                        best_s |= (0 << b)
                    elif bit == 1 and R_child[curr] != 0:
                        curr = R_child[curr]
                        best_s |= (1 << b)
                    elif L_child[curr] != 0:
                        curr = L_child[curr]
                        best_s |= (0 << b)
                    elif R_child[curr] != 0:
                        curr = R_child[curr]
                        best_s |= (1 << b)
            return val ^ best_s
            
        def transform_xor(root, V):
            def _tr(node, b):
                if node == 0 or b < 0:
                    return node
                nn = clone(node)
                if (V >> b) & 1:
                    L_child[nn] = _tr(R_child[node], b - 1)
                    R_child[nn] = _tr(L_child[node], b - 1)
                else:
                    L_child[nn] = _tr(L_child[node], b - 1)
                    R_child[nn] = _tr(R_child[node], b - 1)
                return nn
            return _tr(root, 29)
            
        roots = [0] * (N + 1)
        
        for i in range(1, N + 1):
            if vis[i] == 0:
                curr = i
                path = []
                while vis[curr] == 0:
                    vis[curr] = 1
                    path.append(curr)
                    curr = A[curr]
                if vis[curr] == 1:
                    cycle = []
                    while path:
                        node = path.pop()
                        cycle.append(node)
                        if node == curr:
                            break
                    cycle.reverse()
                    
                    L = len(cycle)
                    c_vals = [V[c] for c in cycle]
                    C = 0
                    for v in c_vals:
                        C ^= v
                        
                    arr = c_vals + c_vals
                    pref = [0] * (2 * L + 1)
                    for j in range(2 * L):
                        pref[j+1] = pref[j] ^ arr[j]
                        
                    for ci in range(L):
                        node_c = cycle[ci]
                        r = 0
                        cycle_vals = []
                        for k in range(1, L + 1):
                            val = pref[ci + k] ^ pref[ci]
                            cycle_vals.append(val)
                            r = insert_val(r, val)
                            if C != 0:
                                cycle_vals.append(val ^ C)
                                r = insert_val(r, val ^ C)
                        roots[node_c] = r
                        ans[node_c] = max(cycle_vals)
                        
                for node in path:
                    vis[node] = 2
                    
        queue = deque()
        for i in range(1, N + 1):
            if roots[i] != 0:
                queue.append(i)
                
        while queue:
            x = queue.popleft()
            for u in rev_adj[x]:
                if roots[u] == 0:
                    ans[u] = max(V[u], query_max(roots[x], V[u]))
                    roots[u] = insert_val(transform_xor(roots[x], V[u]), V[u])
                    queue.append(u)
                    
        out.append(" ".join(str(ans[i]) for i in range(1, N + 1)))
        
    print("\n".join(out))

if __name__ == '__main__':
    solve()