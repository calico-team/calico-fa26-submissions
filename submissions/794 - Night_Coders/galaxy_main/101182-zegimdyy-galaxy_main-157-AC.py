def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i], and "NO"
    otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    """
     
    allocate = list(range(N * M * 2))



    con = [1] * (N * M * 2)

    
    def find(x):
        if allocate[x] != x:


            allocate[x] = find(allocate[x])
        return allocate[x]

    
    def connect(a, b):
        a = find(a)



        b = find(b)


        if a != b:
            if con[a] < con[b]:

                a, b = b, a

            allocate[b] = a

            con[a] += con[b]

    
    def connector(r, c, mode):


        return (r * M + c) * 2 + mode

    
    def act_tile(r, c, mode):
        if G[r][c] == '.':


            return True

        if mode == 0:
            return G[r][c] == 'B'

        return G[r][c] == 'R'

    
    for r in range(N):

        for c in range(M):

            
            if G[r][c] == '.':



                connect(
                    connector(r, c, 0),


                    connector(r, c, 1)
                )

            
            for mode in range(2):

                if not act_tile(r, c, mode):

                    continue

                current = connector(r, c, mode)

                for nrow, ncolol in [(r + 1, c), (r, c + 1)]:

                    if nrow < N and ncolol < M:

                        if act_tile(nrow, ncolol, mode):
                            connect(

                                current,


                                connector(nrow, ncolol, mode)
                            )

    
    answers = []

    for i in range(Q):

        sr, sc = start[i]
        er, ec = end[i]

        source = find(connector(sr, sc, 0))

       
        okay = False

        if G[er][ec] == '.' or G[er][ec] == 'B':


            if source == find(connector(er, ec, 0)):



                okay = True

        if G[er][ec] == '.' or G[er][ec] == 'R':


            if source == find(connector(er, ec, 1)):


                okay = True

        if okay:

            answers.append("YES")




        else:

            answers.append("NO")




    return answers

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)

if __name__ == '__main__':
    main()
