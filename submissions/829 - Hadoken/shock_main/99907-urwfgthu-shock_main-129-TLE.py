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

    def find(x):
        root = x
        while next_cell[root] != root:
            root = next_cell[root]
        while next_cell[x] != root:
            next_cell[x], x = root, next_cell[x]
        return root

    cache_dict = {}
    for R, C, P in reversed(earthquakes):
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
            d = abs(r - R)
            w = widths[d]
            row_base = r * row_width
            row = result[r]
            last_index = row_base + C + w
            i = find(row_base + C - w)
            while i <= last_index:
                c = i - row_base
                row[c] = center_value - d * d - (c - C) ** 2
                next_cell[i] = i + 1
                i = find(i + 1)

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