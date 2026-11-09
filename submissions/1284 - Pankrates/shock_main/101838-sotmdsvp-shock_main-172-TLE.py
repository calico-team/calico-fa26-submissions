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

    grid = [[0] * M for _ in range(N)]

    for i in range(Q):
        for row in range(earthquakes[i][0] - earthquakes[i][2], earthquakes[i][0] + earthquakes[i][2] + 1):
            for col in range(earthquakes[i][1] - earthquakes[i][2], earthquakes[i][1] + earthquakes[i][2] + 1):
                dist = (row - earthquakes[i][0]) * (row - earthquakes[i][0]) + (col - earthquakes[i][1]) * (col - earthquakes[i][1])
                p2 = earthquakes[i][2] * earthquakes[i][2]
                if dist <= p2:
                    grid[row][col] = p2 - dist + 1

    # print(grid[3][3])

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