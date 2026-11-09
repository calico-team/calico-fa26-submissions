import sys
from array import array


def solve():
    data = read_your_input().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out_lines = []
    
    dinosauraus = 0  # (as requested by problem)
    
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
            u = queue[head]
            head += 1
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
        max_nodes = 32 * (N + 2) + 10
        LEFT = array('i', [0]) * max_nodes
        RIGHT = array('i', [0]) * max_nodes
        node_cnt = 1
        
        base_root = node_cnt
        node_cnt += 1
        # base_root mirrors empty
        # Actually p_insert logic: root new node, then 30 levels
        # Since old_root=0, base_root has LEFT=RIGHT=0 initially, then we walk.
        # Let me just inline the insertion of value 0:
        
        # Actually simpler: use p_insert with old_root=0
        # But we need to define p_insert first...
        
        # Let me just inline base_root insertion of 0:
        cur_new = base_root
        for bit in range(29, -1, -1):
            b = 0  # value is 0, all bits 0
            new_child = node_cnt
            node_cnt += 1
            # b=0, so go LEFT
            LEFT[cur_new] = new_child
            RIGHT[cur_new] = 0
            cur_new = new_child
        
        # Now LEFT[base_root] points to path of 0s, RIGHT[base_root] = 0.
        # Hmm but for the last node (leaf), LEFT and RIGHT are 0 by default.
        # Good.
        
        def p_insert(old_root, val):
            nonlocal node_cnt
            new_root = node_cnt
            node_cnt += 1
            LEFT[new_root] = LEFT[old_root]
            RIGHT[new_root] = RIGHT[old_root]
            
            cur_new = new_root
            cur_old = old_root
            
            for bit in range(29, -1, -1):
                b = (val >> bit) & 1
                if b == 0:
                    old_child = LEFT[cur_old]
                    new_child = node_cnt
                    node_cnt += 1
                    LEFT[new_child] = LEFT[old_child]
                    RIGHT[new_child] = RIGHT[old_child]
                    LEFT[cur_new] = new_child
                else:
                    old_child = RIGHT[cur_old]
                    new_child = node_cnt
                    node_cnt += 1
                    LEFT[new_child] = LEFT[old_child]
                    RIGHT[new_child] = RIGHT[old_child]
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
        
        visited = [False] * (N + 1)
        
        for start in range(1, N + 1):
            if in_cycle[start] and not visited[start]:
                # collect cycle
                cyc = []
                cur = start
                while not visited[cur]:
                    visited[cur] = True
                    cyc.append(cur)
                    cur = A[cur]
                
                cp = []
                x = 0
                for node in cyc:
                    x ^= V[node]
                    cp.append(x)
                X = x
                
                # cycle trie
                ch0 = [0]
                ch1 = [0]
                c_root = 0
                for c in cp:
                    # insert c
                    if c_root == 0:
                        c_root = len(ch0)
                        ch0.append(0); ch1.append(0)
                    cur_t = c_root
                    for bit in range(29, -1, -1):
                        b = (c >> bit) & 1
                        if b == 0:
                            nxt = ch0[cur_t]
                            if nxt == 0:
                                nxt = len(ch0)
                                ch0.append(0); ch1.append(0)
                                ch0[cur_t] = nxt
                            cur_t = nxt
                        else:
                            nxt = ch1[cur_t]
                            if nxt == 0:
                                nxt = len(ch0)
                                ch0.append(0); ch1.append(0)
                                ch1[cur_t] = nxt
                            cur_t = nxt
                    # insert c ^ X
                    cc = c ^ X
                    cur_t = c_root
                    for bit in range(29, -1, -1):
                        b = (cc >> bit) & 1
                        if b == 0:
                            nxt = ch0[cur_t]
                            if nxt == 0:
                                nxt = len(ch0)
                                ch0.append(0); ch1.append(0)
                                ch0[cur_t] = nxt
                            cur_t = nxt
                        else:
                            nxt = ch1[cur_t]
                            if nxt == 0:
                                nxt = len(ch0)
                                ch0.append(0); ch1.append(0)
                                ch1[cur_t] = nxt
                            cur_t = nxt
                
                def c_query(key):
                    cur_t = c_root
                    res = 0
                    for bit in range(29, -1, -1):
                        b = (key >> bit) & 1
                        if b == 0:
                            if ch1[cur_t]:
                                res |= (1 << bit)
                                cur_t = ch1[cur_t]
                            else:
                                cur_t = ch0[cur_t]
                        else:
                            if ch0[cur_t]:
                                res |= (1 << bit)
                                cur_t = ch0[cur_t]
                            else:
                                cur_t = ch1[cur_t]
                    return res
                
                # process cycle nodes
                base_of_cycle = {}
                for idx, node in enumerate(cyc):
                    bc = cp[idx - 1] if idx > 0 else 0
                    base_of_cycle[node] = bc
                    ans[node] = c_query(bc)
                
                # process tree
                stack = []
                for c in cyc:
                    bc = base_of_cycle[c]
                    for u in children[c]:
                        if not in_cycle[u]:
                            tag_u = V[u]
                            tree_max = p_query(base_root, tag_u)
                            D_u = V[u]
                            cyc_val = c_query(D_u ^ bc)
                            ans[u] = tree_max if tree_max > cyc_val else cyc_val
                            stack.append((u, base_root, tag_u, D_u, bc))
                
                while stack:
                    u, root_u, tag_u, D_u, bc = stack.pop()
                    for w in children[u]:
                        if not in_cycle[w]:
                            new_tag = tag_u ^ V[w]
                            root_w = p_insert(root_u, tag_u)
                            tree_max = p_query(root_w, new_tag)
                            D_w = V[w] ^ D_u
                            cyc_val = c_query(D_w ^ bc)
                            ans[w] = tree_max if tree_max > cyc_val else cyc_val
                            stack.append((w, root_w, new_tag, D_w, bc))
        
        out_lines.append(" ".join(str(ans[i]) for i in range(1, N + 1)))
    
    sys.stdout.write("\n".join(out_lines))


def read_your_input():
    return sys.stdin.buffer.read()


if __name__ == "__main__":
    solve()