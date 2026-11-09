from bisect import bisect_left, bisect_right

def solve(N: int, K: int, L: list):
    groups = {}
    for X, Y, Z, D in L:
        s = X + Y
        if s not in groups:
            groups[s] = ([], [])
        if D == 'E':
            groups[s][0].append(X)
        else:
            groups[s][1].append(X)

    blocked = 0
    for east_xs, north_xs in groups.values():
        if not east_xs or not north_xs:
            continue
        north_xs.sort()
        for x in east_xs:
            blocked += bisect_right(north_xs, x + K - 1) - bisect_left(north_xs, x)

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