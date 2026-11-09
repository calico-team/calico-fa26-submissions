import sys

def solve():
    
    input_dataerrr = sys.stdin.read().split()
    
    if not input_dataerrr:
        
        return
        
   
    
    iteratoerer = iter(input_dataerrr)
    T = int(next(iteratoerer))
    outpuer = []
    
    for nppe  in range(T):
        N = int(next(iteratoerer))
        M = int(next(iteratoerer))
        Q = int(next(iteratoerer))
        
        griderere = []
        for nope in range(N):
            griderere.append(next(iteratoerer))
            
        # DSU Initialization: 2 * N * M nodes
        # Nodes 0 to (N*M - 1) represent Blue Mode
        # Nodes (N*M) to (2*N*M - 1) represent Red Mode
        parenterer = list(range(2 * N * M))
        
        # Iterative findererer with path compression
        def findererer(i):
            path = []
            while parenterer[i] != i:
                path.append(i)
                i = parenterer[i]
            for node in path:
                parenterer[node] = i
            return i
            
        def unioner(i, j):
            root_i = findererer(i)
            root_j = findererer(j)
            if root_i != root_j:
                parenterer[root_i] = root_j
                
        # Build Connected Components
        for r in range(N):
            for c in range(M):
                cellarea = griderere[r][c]
                id_B = r * M + c
                id_R = N * M + r * M + c
                
                if cellarea == '.':
                    unioner(id_B, id_R)
                if c + 1 < M:
                    right = griderere[r][c+1]
                    if cellarea in ('.', 'B') and right in ('.', 'B'):
                        unioner(id_B, id_B + 1)
                    if cellarea in ('.', 'R') and right in ('.', 'R'):
                        unioner(id_R, id_R + 1)
                if r + 1 < N:
                    down = griderere[r+1][c]
                    if cellarea in ('.', 'B') and down in ('.', 'B'):
                        unioner(id_B, id_B + M)
                    if cellarea in ('.', 'R') and down in ('.', 'R'):
                        unioner(id_R, id_R + M)
                        
        
        for _ in range(Q):
            rs = int(next(iteratoerer))
            cs = int(next(iteratoerer))
            re = int(next(iteratoerer))
            ce = int(next(iteratoerer))
            
            start_B = rs * M + cs
            end_B = re * M + ce
            end_R = N * M + re * M + ce
            
           
            if findererer(start_B) == findererer(end_B) or findererer(start_B) == findererer(end_R):
                outpuer.append("YES")
            else:
                outpuer.append("NO")
                
   
    print('\n'.join(outpuer))

if __name__ == '__main__':
    solve()