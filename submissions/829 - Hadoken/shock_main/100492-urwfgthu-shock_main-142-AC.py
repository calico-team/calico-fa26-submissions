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
    row_width = M + 1
    next_cell = list(range(N * row_width))
    result = [[0] * M for _ in range(N)]
    total_left = N * M  

    cache_dict = {}
    for R, C, P in reversed(earthquakes):
        if total_left == 0:
            break 

        if P not in cache_dict:
            widths_list = []
            w = P
            for d in range(P + 1):
                while w * w + d * d > P * P:
                    w -= 1
                widths_list.append(w)
            cache_dict[P] = widths_list
        widths = cache_dict[P]
        center_value = P * P + 1

        for r in range(R - P, R + P + 1):
            d = r - R if r >= R else R - r
            w = widths[d]
            row_base = r * row_width
            last_index = row_base + C + w

            i = row_base + C - w
            while next_cell[i] != i:
                next_cell[i] = next_cell[next_cell[i]]
                i = next_cell[i]

            if i > last_index:
                continue  

            row = result[r]
            row_value = center_value - d * d
            while i <= last_index:
                c = i - row_base
                t = c - C
                row[c] = row_value - t * t
                total_left -= 1
                next_cell[i] = i + 1
                i += 1
                while next_cell[i] != i:
                    next_cell[i] = next_cell[next_cell[i]]
                    i = next_cell[i]

    return result



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