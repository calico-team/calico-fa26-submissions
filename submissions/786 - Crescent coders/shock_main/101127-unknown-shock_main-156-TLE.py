
import sys
from math import isqrt

def solve():
    input = sys.stdin.buffer.readline
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        earthquakes = [
            tuple(map(int, input().split()))
            for _ in range(Q)
        ]

        grid = [0] * (N * M)

        
        width = M + 1
        parent = list(range(N * width))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        
        for R, C, P in reversed(earthquakes):
            power2 = P * P

            for r in range(R - P, R + P + 1):
                dr = r - R

              
                reach = isqrt(power2 - dr * dr)

                base = r * width
                left = base + C - reach
                right = base + C + reach

                
                x = find(left)

                while x <= right:
                    c = x - base

                    shock = (
                        power2
                        - dr * dr
                        - (c - C) ** 2
                        + 1
                    )

                    grid[r * M + c] = shock

                    
                    parent[x] = find(x + 1)
                    x = parent[x]

       
        for r in range(N):
            print(*grid[r * M:(r + 1) * M])


if __name__ == "__main__":
    solve()
