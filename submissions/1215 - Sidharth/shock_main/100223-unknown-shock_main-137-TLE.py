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
import math 


def solve(N, M, Q, earthquakes):
    # YOUR CODE HERE
    ans = [0] * (N *M)
    jump = list(range(N * M + 1))
    for i in range(Q-1, -1, -1):
        row = earthquakes[i][0]
        col = earthquakes[i][1]
        power=earthquakes[i][2]

        for r in range(row-power, row + power+1):
            row_dist=r-row
            leftover=power*power-row_dist*row_dist
            width = math.isqrt(leftover)
            first = r*M+col-width
            last = r*M+col+width

            cell=first
            while cell <= last:
                start=cell
                while jump[start] != start:
                    start=jump[start]

                while jump[cell] != start:
                    temp = jump[cell]
                    jump[cell] = start
                    cell = temp
                cell = start

                if cell > last:
                    break
                c = cell-r*M
                col_dist = c-col
                ans[cell] = power*power - (row_dist*row_dist +col_dist * col_dist) + 1
                jump[cell] = cell+1
                cell = cell+1

    final=[]
    for r in range(N):
        final.append(ans[r*M:(r+1)*M])
    return final

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