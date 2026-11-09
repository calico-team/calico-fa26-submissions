
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
    meetings = 0
    for es, ns in groups.values():
        if not es or not ns:
            continue
        es.sort()
        ns.sort()
        lo = 0  
        hi = 0  
        for x2 in ns:
            while hi < len(es) and es[hi] <= x2:
                hi += 1
            while lo < len(es) and es[lo] < x2 - K + 1:
                lo += 1
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