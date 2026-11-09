import sys

def solve():
    input_data_terminal = sys.stdin.read().split()
    if not input_data_terminal:
        return
    iterator_var = iter(input_data_terminal)
    T = int(next(iterator_var))
    outputeer = []






    
    for nope in range(T):
        N = int(next(iterator_var))
        M = int(next(iterator_var))
        Q = int(next(iterator_var))
        
        griddd = []
        for nope in range(N):
            griddd.append(next(iterator_var))
        parenteeerer = list(range(2 * N * M))
        def findererer(i):
            way = []
            while parenteeerer[i] != i:
                way.append(i)
                i = parenteeerer[i]
            for node in way:
                parenteeerer[node] = i
            return i
        def union_node(i, j):
            root_i = findererer(i)
            root_j = findererer(j)
            if root_i != root_j:
                parenteeerer[root_i] = root_j

        for r in range(N):
            for c in range(M):
                cell_node = griddd[r][c]     
                id_Bottom = r * M + c
                id_right = N * M + r * M + c  
                if cell_node == '.':
                    union_node(id_Bottom, id_right)
                if c + 1 < M:
                    right = griddd[r][c+1]
                    if cell_node in ('.', 'B') and right in ('.', 'B'):
                        union_node(id_Bottom, id_Bottom + 1)
                    if cell_node in ('.', 'R') and right in ('.', 'R'):
                        union_node(id_right, id_right + 1)
                if r + 1 < N:
                    down = griddd[r+1][c]
                    if cell_node in ('.', 'B') and down in ('.', 'B'):
                        union_node(id_Bottom, id_Bottom + M)
                    if cell_node in ('.', 'R') and down in ('.', 'R'):
                        union_node(id_right, id_right + M)
        for nope in range(Q):
            rs = int(next(iterator_var))
            cs = int(next(iterator_var))
            re = int(next(iterator_var))
            ce = int(next(iterator_var))
            start_B = rs * M + cs
            end_B = re * M + ce
            end_R = N * M + re * M + ce
            if findererer(start_B) == findererer(end_B) or findererer(start_B) == findererer(end_R):
                outputeer.append("YES")
            else:
                outputeer.append("NO")
    print('\n'.join(outputeer))

if __name__ == '__main__':
    solve()