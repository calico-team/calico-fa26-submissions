def solve(N: int, K: int, L: list):
    groups = {}

    for X, Y, Z, D in L:
        s = X + Y
        if s not in groups:
            groups[s] = [[], []]
        if D == 'E':
            groups[s][0].append(X)
        else:
            groups[s][1].append(X)

    meetings = 0
    for east, north in groups.values():
        east.sort()
        north.sort()
        lo = hi = 0
        for x1 in east:
            while lo < len(north) and north[lo] < x1:
                lo += 1
            while hi < len(north) and north[hi] <= x1 + K - 1:
                hi += 1
            meetings += hi - lo

    return N * K - meetings

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
