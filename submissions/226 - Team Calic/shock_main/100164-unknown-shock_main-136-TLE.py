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
_cache = {}

def _widths(P):
    # wf[k] = floor(sqrt(P^2 - (k-P)^2)) for k = 0..2P  (row offset dy = k-P)
    wf = _cache.get(P)
    if wf is None:
        pp = P * P
        half = []
        cur = P
        for dy in range(P + 1):
            while cur * cur + dy * dy > pp:
                cur -= 1
            half.append(cur)
        wf = half[:0:-1] + half      # dy = -P .. -1, then 0 .. P
        _cache[P] = wf
    return wf


def solve(N, M, Q, earthquakes):
    total = N * M
    painted = bytearray(total)
    res = [0] * total
    left = total
    find = painted.find

    # process in reverse: the last earthquake to touch a cell decides its value
    for i in range(Q - 1, -1, -1):
        R, C, P = earthquakes[i]
        wf = _widths(P)
        top = P * P + 1
        pos = (R - P) * M + C        # flat index of (row R+dy, column C), starting at dy = -P
        dy = -P
        for h in wf:
            hi = pos + h + 1
            c = find(0, pos - h, hi)
            if c != -1:
                base = top - dy * dy
                while c != -1:
                    painted[c] = 1
                    d = c - pos
                    res[c] = base - d * d
                    left -= 1
                    c = find(0, c + 1, hi)
            pos += M
            dy += 1
        if left == 0:
            break

    return [res[r * M:(r + 1) * M] for r in range(N)]

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