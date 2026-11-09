import sys

sys.setrecursionlimit(300000)

class FastTrie:
    def __init__(self, capacity):
        self.left = [0] * capacity
        self.right = [0] * capacity
        self.cnt = [0] * capacity
        self.size = 1

    def insert(self, val):
        curr = 0
        self.cnt[curr] += 1
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            if bit == 0:
                nxt = self.left[curr]
                if not nxt:
                    nxt = self.size
                    self.left[curr] = nxt
                    self.size += 1
                curr = nxt
            else:
                nxt = self.right[curr]
                if not nxt:
                    nxt = self.size
                    self.right[curr] = nxt
                    self.size += 1
                curr = nxt
            self.cnt[curr] += 1

    def remove(self, val):
        curr = 0
        self.cnt[curr] -= 1
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            if bit == 0:
                curr = self.left[curr]
            else:
                curr = self.right[curr]
            self.cnt[curr] -= 1

    def query(self, val):
        curr = 0
        res = 0
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            target = 1 - bit
            if target == 0:
                nxt = self.left[curr]
                if nxt and self.cnt[nxt] > 0:
                    res |= (1 << i)
                    curr = nxt
                else:
                    curr = self.right[curr]
            else:
                nxt = self.right[curr]
                if nxt and self.cnt[nxt] > 0:
                    res |= (1 << i)
                    curr = nxt
                else:
                    curr = self.left[curr]
        return res

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
        A = [int(x) - 1 for x in input_data[idx:idx+N]]
        idx += N
        V = [int(x) for x in input_data[idx:idx+N]]
        idx += N
        
        rev_adj = [[] for _ in range(N)]
        for i in range(N):
            rev_adj[A[i]].append(i)
            
        vis = [0] * N
        ans = [0] * N
        
        for i in range(N):
            if vis[i] == 0:
                curr = i
                path = []
                while vis[curr] == 0:
                    vis[curr] = 1
                    path.append(curr)
                    curr = A[curr]
                
                if vis[curr] == 1:
                    cycle_start = path.index(curr)
                    cycle = path[cycle_start:]
                    L = len(cycle)
                    
                    doubled = cycle + cycle
                    pref = [0] * (2 * L + 1)
                    for k in range(2 * L):
                        pref[k+1] = pref[k] ^ V[doubled[k]]
                    
                    cycle_trie = FastTrie(2 * L * 32 + 5)
                    for m in range(2 * L + 1):
                        cycle_trie.insert(pref[m])
                        
                    for j in range(L):
                        c_node = cycle[j]
                        anc_trie = FastTrie((N + 5) * 32)
                        
                        def dfs(u, cur_Xor):
                            res_cycle = cycle_trie.query(cur_Xor ^ pref[j])
                            res_tree = anc_trie.query(cur_Xor)
                            ans[u] = max(res_cycle, res_tree)
                            
                            anc_trie.insert(cur_Xor)
                            for v in rev_adj[u]:
                                dfs(v, cur_Xor ^ V[v])
                            anc_trie.remove(cur_Xor)
                        
                        dfs(c_node, V[c_node])
                
                for node in path:
                    vis[node] = 2
        
        out.append(" ".join(map(str, ans)))
        
    print("\n".join(out))

if __name__ == '__main__':
    solve()