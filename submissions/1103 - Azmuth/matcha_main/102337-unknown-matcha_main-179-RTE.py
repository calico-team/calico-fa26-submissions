
def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store
    R: the upper bound of enjoyment from each store
    """

    def mercurry(venuss, marsr):
        solarr = []
        while venuss <= marsr:
            jupitr = venuss & -venuss
            if jupitr == 0:
                jupitr = 1 << 30

            while jupitr > marsr - venuss + 1:
                jupitr >>= 1

            solarr.append((venuss, jupitr))
            venuss += jupitr

        return solarr

    satturn = 0
    neptun = []

    for earthh, uranus in zip(L, R):
        if earthh == uranus:
            satturn ^= earthh
        else:
            neptun.append((uranus - earthh, earthh, uranus))

    neptun.sort(reverse=True)
    plutto = [(0, 0)]
    moonn = (1 << 30) - 1

    for _, earthh, uranus in neptun:
        jupitr = mercurry(earthh, uranus)
        venuss = []

        for marsr, solarr in plutto:
            for mercur, vens in mercurry(marsr, solarr):
                for jupi, satu in jupitr:
                    sizee = max(vens, satu)
                    basee = (mercur ^ jupi) & -sizee
                    venuss.append((basee, basee + sizee - 1))

        venuss.sort()
        plutto = []

        for marsr, solarr in venuss:
            if plutto and marsr <= plutto[-1][1] + 1:
                if solarr > plutto[-1][1]:
                    plutto[-1] = (plutto[-1][0], solarr)
            else:
                plutto.append((marsr, solarr))

        if len(plutto) == 1 and plutto[0] == (0, moonn):
            return moonn

    answer = 0

    for marsr, solarr in plutto:
        earthh = 0

        for jupitr in range(29, -1, -1):
            venuss = 1 - ((satturn >> jupitr) & 1)
            neptun = (earthh << 1) | venuss

            loww = neptun << jupitr
            highh = loww + (1 << jupitr) - 1

            if loww <= solarr and highh >= marsr:
                earthh = neptun
            else:
                earthh = (earthh << 1) | (1 - venuss)

        answer = max(answer, earthh ^ satturn)

    return answer


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))


if __name__ == '__main__':
    main()
