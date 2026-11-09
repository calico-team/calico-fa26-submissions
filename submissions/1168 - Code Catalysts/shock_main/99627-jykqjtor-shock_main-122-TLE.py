from math import isqrt


def solve(N, M, Q, earthquakes):
    W = M + 1
    nxt = list(range(N * W))
    res = [0] * (N * W)
    remaining = N * M

    def find(i):
        root = i
        while nxt[root] != root:
            root = nxt[root]
        while nxt[i] != root:
            nxt[i], i = root, nxt[i]
        return root

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break
        pp = P * P
        for r in range(R - P, R + P + 1):
            dr = r - R
            rem = pp - dr * dr
            w = isqrt(rem)
            base = r * W
            center = base + C
            hi = center + w
            i = find(center - w)
            while i <= hi:
                dc = i - center
                res[i] = rem - dc * dc + 1
                remaining -= 1
                nxt[i] = i + 1
                i = find(i + 1)

    return [res[r * W:r * W + M] for r in range(N)]


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