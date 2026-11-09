from bisect import bisect_left, bisect_right
 
 
def solve(N, K, L):
    east = {}
    north = {}
    for x, y, z, d in L:
        if d == 'E':
            east.setdefault(x + y, []).append(x)
        else:
            north.setdefault(x + y, []).append(x)
    collisions = 0
    for s, nx in north.items():
        ex = east.get(s)
        if not ex:
            continue
        ex.sort()
        for xj in nx:
            lo = bisect_left(ex, xj - K + 1)
            hi = bisect_right(ex, xj)
            if hi > lo:
                collisions += hi - lo
    return N * K - collisions
 
 
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
 