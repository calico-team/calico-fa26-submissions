import sys
from array import array

def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out_lines = []
    
    for _ in range(T):
        N = int(next(it))
        A = [0] * (N + 1)
        V = [0] * (N + 1)
        for i in range(1, N + 1):
            A[i] = int(next(it))
        for i in range(1, N + 1):
            V[i] = int(next(it))
        
        children = [[] for _ in range(N + 1)]
        indeg = [0] * (N + 1)
        for i in range(1, N + 1):
            p = A[i]
            children[p].append(i)
            indeg[p] += 1
        
        queue = [i for i in range(1, N + 1) if indeg[i] == 0]
        head = 0
        while head < len(queue):
            u = queue[head]; head += 1
            v = A[u]
            indeg[v] -= 1
            if indeg[v] == 0:
                queue.append(v)
        
        in_cycle = [False] * (N + 1)
        for i in range(1, N + 1):
            if indeg[i] > 0:
                in_cycle[i] = True
        
        ans = [0] * (N + 1)
        
        # Persistent trie
        max_nodes = 30 * (N + 2) + 10
        LEFT = array('i', [0]) * max_nodes
        RIGHT = array('i', [0]) * max_nodes
        node_cnt = [0]  # mutable for closure
        
        # Actually, let me avoid closures with node_cnt list. Use class or just inline.
        
        def p_insert(old_root, val):
            new_root = node_cnt[0]
            node_cnt[0] += 1
            LEFT[new_root] = LEFT[old_root] if old_root else 0
            RIGHT[new_root] = RIGHT[old_root] if old_root else 0
            
            cur_new = new_root
            cur_old = old_root
            
            for bit in range(29, -1, -1):
                b = (val >> bit) & 1
                if b == 0:
                    old_child = LEFT[cur_old] if cur_old else 0
                    new_child = node_cnt[0]
                    node_cnt[0] += 1
                    LEFT[new_child] = LEFT[old_child] if old_child else 0
                    RIGHT[new_child] = RIGHT[old_child] if old_child else 0
                    LEFT[cur_new] = new_child
                else:
                    old_child = RIGHT[cur_old] if cur_old else 0
                    new_child = node_cnt[0]
                    node_cnt[0] += 1
                    LEFT[new_child] = LEFT[old_child] if old_child else 0
                    RIGHT[new_child] = RIGHT[old_child] if old_child else 0
                    RIGHT[cur_new] = new_child
                cur_new = new_child
                cur_old = old_child
            return new_root
        
        def p_query(root, key):
            cur = root
            res = 0
            for bit in range(29, -1, -1):
                if cur == 0:
                    break
                b = (key >> bit) & 1
                if b == 0:
                    if RIGHT[cur]:
                        res |= (1 << bit)
                        cur = RIGHT[cur]
                    else:
                        cur = LEFT[cur]
                else:
                    if LEFT[cur]:
                        res |= (1 << bit)
                        cur = LEFT[cur]
                    else:
                        cur = RIGHT[cur]
            return res
        
        # Initialize with empty trie (just root node = 0 means empty)
        node_cnt[0] = 1  # root is node 0 (null sentinel) - hmm actually 0 means null
        
        # Hmm, actually 0 as sentinel is fine. When we insert first value:
        # old_root = 0, new_root = 1 (first real node). Good.