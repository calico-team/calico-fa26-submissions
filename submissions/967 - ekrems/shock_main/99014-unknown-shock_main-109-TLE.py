from math import isqrt


def solve(N, M, Q, earthquakes):
    genislik = M + 1
    atla = list(range(N * genislik))
    harita = [[0] * M for _ in range(N)]

    def ilk_bos(i):
        while atla[i] != i:
            atla[i] = atla[atla[i]]
            i = atla[i]
        return i

    def satiri_boya(satir, sutun, guc, fark):
        guc2 = guc * guc
        yaricap = isqrt(guc2 - fark * fark)
        hedef = satir + fark
        taban = hedef * genislik
        merkez = taban + sutun

        i = ilk_bos(merkez - yaricap)
        while i <= merkez + yaricap:
            yatay = i - merkez
            harita[hedef][i - taban] = guc2 - fark * fark - yatay * yatay + 1
            atla[i] = i + 1
            i = ilk_bos(i + 1)

    for satir, sutun, guc in reversed(earthquakes):
        for fark in range(-guc, guc + 1):
            satiri_boya(satir, sutun, guc, fark)

    return harita


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()