import sys

class Trie:
    def __init__(self):
        self.nodes = [[0, 0]]
        self.cnt = [0]

    def insert(self, val):
        curr = 0
        self.cnt[curr] += 1
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            if not self.nodes[curr][bit]:
                self.nodes.append([0, 0])
                self.cnt.append(0)
                self.nodes[curr][bit] = len(self.nodes) - 1
            curr = self.nodes[curr][bit]
            self.cnt[curr] += 1

    def remove(self, val):
        curr = 0
        self.cnt[curr] -= 1
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            curr = self.nodes[curr][bit]
            self.cnt[curr] -= 1

    def query(self, val):
        curr = 0
        res = 0
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            target = 1 - bit
            if self.nodes[curr][target] and self.cnt[self.nodes[curr][target]] > 0:
                res |= (1 << i)
                curr = self.nodes[curr][target]
            else:
                curr = self.nodes[curr][bit]
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
                    
                    cycle_trie = Trie()
                    for m in range(2 * L):
                        cycle_trie.insert(pref[m+1] ^ pref[0])
                        
                    for j in range(L):
                        c_node = cycle[j]
                        curr_T = V[c_node]
                        c_idx = j
                        anc_trie = Trie()
                        stack = [(c_node, curr_T, c_idx, 0)]
                        
                        while stack:
                            u, cur_T, ci, state = stack.pop()
                            if state == 0:
                                res = cycle_trie.query(cur_T ^ pref[ci])
                                res = max(res, anc_trie.query(cur_T))
                                ans[u] = res
                                
                                anc_trie.insert(cur_T)
                                stack.append((u, cur_T, ci, 1))
                                
                                for v in rev_adj[u]:
                                    stack.append((v, cur_T ^ V[v], ci, 0))
                            else:
                                anc_trie.remove(cur_T)
                
                for node in path:
                    vis[node] = 2
        
        out.append(" ".join(map(str, ans)))
        
    print("\n".join(out))

if __name__ == '__main__':
    solve()