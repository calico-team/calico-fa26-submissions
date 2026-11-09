def solve():
    data = sys.stdin.buffer.read().split()
    if not data: return
    it = iter(data)
    T = int(next(it))
    out_lines = []
    
    for _ in range(T):
        N = int(next(it))
        A = [0] * (N + 1)
        V = [0] * (N + 1)
        for i in range(1, N + 1): A[i] = int(next(it))
        for i in range(1, N + 1): V[i] = int(next(it))
        
        children = [[] for _ in range(N + 1)]
        indeg = [0] * (N + 1)
        for i in range(1, N + 1):
            p = A[i]
            children[p].append(i)
            indeg[p] += 1
        
        # Peel
        queue = [i for i in range(1, N + 1) if indeg[i] == 0]
        head = 0
        while head < len(queue):
            u = queue[head]; head += 1
            v = A[u]
            indeg[v] -= 1
            if indeg[v] == 0: queue.append(v)
        
        in_cycle = [False] * (N + 1)
        for i in range(1, N + 1):
            if indeg[i] > 0: in_cycle[i] = True
        
        ans = [0] * (N + 1)
        
        # Persistent trie arrays (preallocated)
        max_nodes = 30 * (N + 2) + 10
        LEFT = array('i', [0]) * max_nodes  # hmm this won't work