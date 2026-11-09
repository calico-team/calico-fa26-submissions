def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    komsu = [[] for _ in range(N + 1)]
    for uc1, uc2 in E:
        komsu[uc1].append(uc2)
        komsu[uc2].append(uc1)

    baba = [0] * (N + 1)
    gezildi = [False] * (N + 1)
    gezildi[N] = True
    yigin = [N]
    while yigin:
        simdiki = yigin.pop()
        for sonraki in komsu[simdiki]:
            if not gezildi[sonraki]:
                gezildi[sonraki] = True
                baba[sonraki] = simdiki
                yigin.append(sonraki)

    cikti = []
    yedek = 0
    for dugum in range(1, N):
        cikti.append(baba[dugum])
        yedek ^= baba[dugum]
    cikti.append(yedek)
    return cikti


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    kayip = A.index(-1)
    if kayip != N - 1:
        yedek = 0
        for sira in range(N):
            if sira != kayip:
                yedek ^= A[sira]
        A[kayip] = yedek

    kenarlar = []
    for dugum in range(1, N):
        kenarlar.append((dugum, A[dugum - 1]))
    return kenarlar


def main():
    phase = input()
    N = int(input())
    if phase == 'FIRST':
        E = []
        for _ in range(N - 1):
            u, v = map(int, input().split())
            E.append((u, v))
        A = solve_phase1(N, E)
        print(' '.join(map(str, A)))
    else:
        A = list(map(int, input().split()))
        for u, v in solve_phase2(N, A):
            print(u, v)


if __name__ == '__main__':
    main()