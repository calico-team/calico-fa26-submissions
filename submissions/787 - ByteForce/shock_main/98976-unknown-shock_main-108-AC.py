from math import isqrt


def solve(N, M, Q, earthquakes):
    """
    Process earthquakes in reverse: the last earthquake covering a cell decides its
    reading, so each cell only needs to be written once. A per-row "next unwritten
    cell" union-find skips already-written cells.
    """
    S = M + 1                      
    nx = list(range(N * S))
    val = [0] * (N * S)
    hw_cache = {}
    left = N * M
    seen_q = set()
    for qi in range(Q - 1, -1, -1):
        R, C, P = earthquakes[qi]
        if earthquakes[qi] in seen_q:   
            continue
        seen_q.add(earthquakes[qi])
        hw = hw_cache.get(P)
        if hw is None:
            P2 = P * P
            hw = [isqrt(P2 - d * d) for d in range(P + 1)]
            hw_cache[P] = hw
        P2 = P * P
        for dr in range(-P, P + 1):
            w = hw[dr if dr >= 0 else -dr]
            base = (R + dr) * S
            lo = base + C - w
            end = base + C + w
            # find first unwritten cell >= lo
            r = lo
            while nx[r] != r:
                r = nx[r]
            x = lo
            while nx[x] != r:
                nx[x], x = r, nx[x]
            x = r
            if x > end:
                continue
            rem = P2 - dr * dr + 1
            cbase = base + C
            while x <= end:
                d = x - cbase
                val[x] = rem - d * d
                nx[x] = x + 1
                left -= 1
                x += 1
                while nx[x] != x:
                    x = nx[x]
            y = lo
            while y < x and nx[y] != x:
                nxt = nx[y]
                nx[y] = x
                y = nxt
        if left == 0:
            break
    return [val[i * S:i * S + M] for i in range(N)]

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
