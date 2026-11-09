def solve(N: int, M: int, K: int, P: list[int]) -> int:
    derinlik = [0] * (N + 1)
    for i in range(1, N + 1):
        yol = []
        v = i
        while v and derinlik[v] == 0:
            yol.append(v)
            v = P[v - 1]
        d = derinlik[v] if v else 0
        for u in reversed(yol):
            d += 1
            derinlik[u] = d

    say = [0] * (M + 2)
    for i in range(1, N + 1):
        if derinlik[i] <= M:
            say[derinlik[i]] += 1

    cevap = sum(say)
    once = 0
    for j in range(1, M + 1):
        cevap = min(cevap, once + K * (M - j + 1))
        once += say[j]
    return cevap

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()