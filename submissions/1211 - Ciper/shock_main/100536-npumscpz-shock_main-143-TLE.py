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
    W = M + 1                      
    nxt = list(range(N * W))       
    res = [0] * (N * M)
    left = N * M
    width_cache = {}

    def find(x):
        root = x
        while nxt[root] != root:
            root = nxt[root]
        while nxt[x] != root:
            nxt[x], x = root, nxt[x]
        return root

    for R, C, P in reversed(earthquakes):
        if left == 0:
            break

        if P not in width_cache:
            p2 = P * P
            width_cache[P] = [int((p2 - d * d) ** 0.5) for d in range(P + 1)]
            tbl = width_cache[P]
            
            for d in range(P + 1):
                while tbl[d] * tbl[d] > p2 - d * d:
                    tbl[d] -= 1
                while (tbl[d] + 1) ** 2 <= p2 - d * d:
                    tbl[d] += 1
        tbl = width_cache[P]
        p2 = P * P

        for dr in range(-P, P + 1):
            r = R + dr
            half = tbl[abs(dr)]
            base = r * W
            hi = base + C + half
            x = find(base + C - half)
            while x <= hi:
                dc = x - base - C
                res[r * M + x - base] = p2 - dr * dr - dc * dc + 1
                nxt[x] = x + 1
                left -= 1
                x = find(x + 1)

    return [res[i * M:(i + 1) * M] for i in range(N)]


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