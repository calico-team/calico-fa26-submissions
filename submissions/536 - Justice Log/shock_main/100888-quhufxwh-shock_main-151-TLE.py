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
def solve(N, M, Q, earthquakes):
    readings = [[0] * M for _ in range(N)]
    for X,Y,P in earthquakes:
        # X -= 1
        # Y -= 1
        for i in range(N):
            for j in range(M):

                # print(X,Y,P,i,j,  P^2 - (i-X)^2 - (j-Y)^2 + 1, "- ", -(j-Y)^2 )
                new = P**2 - (i-X)**2 - (j-Y)**2 + 1
                if new > 0:
                    readings[i][j] = new
    return readings


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            # X -= 1
            # Y -= 1
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()