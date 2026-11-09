def solve(N: int, M: int, K: int, P: list[int]) -> int:
    depth = [0] * (N + 1)
    for i in range(1, N + 1):
        if depth[i]:
            continue
        path = []
        cur = i
        while cur != 0 and depth[cur] == 0:
            path.append(cur)
            cur = P[cur - 1]
        base = depth[cur] if cur != 0 else 0
        for node in reversed(path):
            base += 1
            depth[node] = base

    maxd = max(depth[1:])
    Dmax = min(M, maxd)
    cnt = [0] * (Dmax + 2)
    for i in range(1, N + 1):
        if depth[i] <= Dmax:
            cnt[depth[i]] += 1

    pref = [0] * (Dmax + 2)  
    for j in range(1, Dmax + 1):
        pref[j] = pref[j - 1] + cnt[j]

    best = 0
    run = float('inf')  
    for D in range(1, Dmax + 1):
        run = min(run, K * (M - D + 1) + pref[D - 1])
        m = run - pref[D - 1]
        if m < 0:
            break
        best = max(best, pref[D - 1] + min(cnt[D], m))
    return best

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()
