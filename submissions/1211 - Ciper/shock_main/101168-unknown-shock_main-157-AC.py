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
    from math import isqrt

    W = M + 1                    
    nxt = list(range(N * W))     
    grid = [0] * (N * M)
    row_left = [M] * N           
    remaining = N * M
    widths_by_power = {}

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break

        widths = widths_by_power.get(P)
        if widths is None:
            widths = [isqrt(P * P - d * d) for d in range(P + 1)]
            widths_by_power[P] = widths

        p2 = P * P
        for dr in range(-P, P + 1):
            r = R + dr
            if row_left[r] == 0:
                continue

            half = widths[dr if dr >= 0 else -dr]
            center = r * W + C
            last = center + half

            
            x = center - half
            root = x
            while nxt[root] != root:
                root = nxt[root]
            while nxt[x] != root:
                nxt[x], x = root, nxt[x]
            x = root

            if x > last:
                continue

            base_val = p2 - dr * dr + 1
            filled = 0
            while x <= last:
                dc = x - center
                grid[x - r] = base_val - dc * dc  
                nxt[x] = x + 1
                filled += 1

                y = x + 1
                root = y
                while nxt[root] != root:
                    root = nxt[root]
                while nxt[y] != root:
                    nxt[y], y = root, nxt[y]
                x = root

            row_left[r] -= filled
            remaining -= filled

    return [grid[i * M:(i + 1) * M] for i in range(N)]

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