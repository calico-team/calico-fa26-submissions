import sys
from math import isqrt

def find(next_free, x):
    while next_free[x] != x:
        next_free[x] = next_free[next_free[x]]
        x = next_free[x]
    return x

def solve(n, m, earthquakes):
    size = n * m
    answer = [0] * size
    next_free = list(range(size + 1))

    for r, c, p in reversed(earthquakes):
        p_squared = p * p

        for row in range(r - p, r + p + 1):
            dr = row - r
            remaining = p_squared - dr * dr
            width = isqrt(remaining)
            base = row * m

            position = find(next_free, base + c - width)
            right = base + c + width

            while position <= right:
                dc = position - base - c
                answer[position] = remaining - dc * dc + 1

                next_free[position] = find(next_free, position + 1)
                position = next_free[position]

    return answer

def main():
    input = sys.stdin.buffer.readline
    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        earthquakes = []
        for _ in range(q):
            r, c, p = map(int, input().split())
            earthquakes.append((r, c, p))

        answer = solve(n, m, earthquakes)

        for row in range(n):
            start = row * m
            sys.stdout.write(" ".join(map(str, answer[start:start+m])) + "\n")

if __name__ == "__main__":
    main()
