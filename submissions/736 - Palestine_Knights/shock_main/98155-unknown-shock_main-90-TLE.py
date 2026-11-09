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
    # YOUR CODE HERE
    Rows = N
    Columns = M

    results = [[0] * Columns for _ in range(Rows)]

    for i in range(Q):
        R = earthquakes[i][0]
        C = earthquakes[i][1]
        P = earthquakes[i][2]

        Pow = (P ** 2) + 1

        for x in range(Rows):
            for y in range(Columns):
                res = Pow - (((x - R)**2) + ((y-C) **2))
                if res > 0:
                    results[x][y] = res

    

    return results


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