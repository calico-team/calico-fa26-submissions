import sys

def solve():
    input = sys.stdin.read().split()
    if not input:
        return
    
    it = iter(input)
    t = int(next(it))
    out = []
    
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))
        
        grid = [next(it) for _ in range(n)]
        
        states = n * m * 2
        parent = list(range(states))
        size = [1] * states

        def get_id(r, c, mode):
            return (r * m + c) * 2 + mode

        def find(x):
            root = x
            while root != parent[root]:
                root = parent[root]
           
            curr = x
            while curr != root:
                nxt = parent[curr]
                parent[curr] = root
                curr = nxt
            return root

        def union(a, b):
            root_a = find(a)
            root_b = find(b)
            if root_a == root_b:
                return
            if size[root_a] < size[root_b]:
                root_a, root_b = root_b, root_a
            parent[root_b] = root_a
            size[root_a] += size[root_b]

        def valid(r, c, mode):
            tile = grid[r][c]
            if tile == '.':
                return True
            if mode == 0 and tile == 'B':
                return True
            if mode == 1 and tile == 'R':
                return True
            return False

   
        for r in range(n):
            for c in range(m):
                
                if grid[r][c] == '.':
                    union(get_id(r, c, 0), get_id(r, c, 1))

                
                for dr, dc in [(0, 1), (1, 0)]:
                    nr, nc = r + dr, c + dc
                    if nr < n and nc < m:
                        for mode in range(2):
                            if valid(r, c, mode) and valid(nr, nc, mode):
                                union(get_id(r, c, mode), get_id(nr, nc, mode))

       
        for _ in range(q):
            r1 = int(next(it))
            c1 = int(next(it))
            r2 = int(next(it))
            c2 = int(next(it))

            start = get_id(r1, c1, 0)
            blue_dest = get_id(r2, c2, 0)
            red_dest = get_id(r2, c2, 1)

            root_start = find(start)
            if root_start == find(blue_dest) or root_start == find(red_dest):
                out.append("YES")
            else:
                out.append("NO")
                
    print('\n'.join(out))

if __name__ == '__main__':
    solve()