
import sys


def solve(N, M, earthquakes):
    grid = [[0] * M for _ in range(N)]
    nxt = [list(range(M + 1)) for _ in range(N)]

    for X, Y, P in reversed(earthquakes):
        PP = P * P

        start = max(0, X - P)
        end = min(N - 1, X + P) + 1

        for r in range(start, end):
            dr = r - X
            w = int((PP - dr * dr) ** 0.5)

            lo = max(0, Y - w)
            hi = min(M - 1, Y + w)

            nr = nxt[r]
            row = grid[r]

            base = PP - dr * dr + 1
            c = lo

            while c <= hi:
                while nr[c] != c:
                    nr[c] = nr[nr[c]]
                    c = nr[c]

                if c > hi:
                    break

                dc = c - Y
                row[c] = base - dc * dc

                nr[c] = c + 1
                c += 1

    return grid


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))

    T = next(data)
    output = []

    for _ in range(T):
        N = next(data)
        M = next(data)
        Q = next(data)

        earthquakes = [
            (next(data), next(data), next(data))
            for _ in range(Q)
        ]

        answer = solve(N, M, earthquakes)

        for row in answer:
            output.append(' '.join(map(str, row)))

        if len(output) >= 1000:
            sys.stdout.write('\n'.join(output) + '\n')
            output.clear()

    if output:
        sys.stdout.write('\n'.join(output) + '\n')


if __name__ == "__main__":
    main()
