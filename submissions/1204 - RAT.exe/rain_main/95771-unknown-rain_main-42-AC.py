from bisect import bisect_left, bisect_right
from collections import defaultdict


def solve(N: int, K: int, L: list):
    east = defaultdict(list)   
    north = defaultdict(list)  

    for X, Y, Z, D in L:
        if D == 'E':
            east[X + Y].append(X)
        else:
            north[X + Y].append(X)

    blocked = 0
    for s, nxs in north.items():
        exs = east.get(s)
        if not exs:
            continue
        exs.sort()
        for xj in nxs:
            
            lo = bisect_left(exs, xj - K + 1)
            hi = bisect_right(exs, xj)
            blocked += hi - lo

    return N * K - blocked

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
        
