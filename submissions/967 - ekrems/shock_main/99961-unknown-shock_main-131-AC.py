from math import isqrt


def solve(N, M, Q, earthquakes):
    genislik = M + 1
    atla = list(range(N * genislik))
    harita = [0] * (N * genislik)
    yaricaplar = {}

    for satir, sutun, guc in reversed(earthquakes):
        if guc not in yaricaplar:
            yaricaplar[guc] = [(f * genislik, isqrt(guc * guc - f * f), guc * guc - f * f + 1)
                               for f in range(-guc, guc + 1)]
        orta = satir * genislik + sutun

        for kayma, yaricap, taban in yaricaplar[guc]:
            merkez = orta + kayma
            bas = merkez - yaricap
            son = merkez + yaricap

            i = atla[bas]
            if i > son and atla[i] == i:
                continue

            while True:
                while atla[i] != i:
                    atla[i] = atla[atla[i]]
                    i = atla[i]
                if i > son:
                    break
                yatay = i - merkez
                harita[i] = taban - yatay * yatay
                atla[i] = i + 1
                i += 1
            atla[bas] = i

    return [harita[r * genislik: r * genislik + M] for r in range(N)]


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