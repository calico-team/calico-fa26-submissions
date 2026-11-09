from bisect import bisect_left, bisect_right
from collections import defaultdict

def solve(N: int, K: int, L: list):
    
    east = defaultdict(list)
    north = defaultdict(list)
    for x, y, z, d in L:
        if d == 'E':
            east[x + y].append(x)
        else:
            north[x + y].append(x)

    lost = 0
    for s, xs_n in north.items():
        xs_e = east.get(s)
        if not xs_e:
            continue
        xs_e.sort()
        for xj in xs_n:
            # E drones jinka X in [xj-K+1, xj]
            lost += bisect_right(xs_e, xj) - bisect_left(xs_e, xj - K + 1)

    return N * K - lost

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()