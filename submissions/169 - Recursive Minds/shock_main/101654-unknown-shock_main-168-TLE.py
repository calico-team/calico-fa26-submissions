"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
*    X: column of the epicenter
*    Y: row of the epicenter
*    P: power of the earthquake
"""
from math import isqrt
def solve(N, M, Q, earthquakes):
    grid= [[0] * M for _ in range(N)]
    next_clm=[list(range(M+1)) for i in range(N)]
    def find(r,c):
        while next_clm[r][c] != c:
            next_clm[r][c] = next_clm[r][next_clm[r][c]]
            c = next_clm[r][c]
        return c
    
    for R,C,P in reversed(earthquakes):
        psq= P*P
        for r in range(R-P,R+P+1):
            dis_y=r-R
            w=isqrt(psq-dis_y*dis_y)
            lft=C-w
            rgt=C+w
            c=find(r,lft)
            while c<=rgt:
                dist_x=c-C
                shock=psq- dist_x*dist_x - dis_y*dis_y +1
                grid[r][c]=shock
                next_clm[r][c]=find(r,c+1)
                c=find(r,c)
    # for R,C,P in earthquakes:
    #     for r in range(R-P, R+P+1):
    #         for c in range(C-P, C+P+1):
    #             shock = P*P -(r-R)*(r-R) - (c-C)*(c-C)+1
    #             if shock > 0:
    #                 grid[r][c] = shock
    return grid



def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()