
"""
Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.

N: number of rows in the grid
M: number of columns in the grid
Q: number of earthquakes
earthquakes: a list of tuples (X, Y, P), where:
    X: column of the epicenter
    Y: row of the epicenter
    P: power of the earthquake
"""

def solve(N, M, Q, earthquakes):
    venuss = [[0] * M for _ in range(N)]
    jupitr = [list(range(M + 1)) for _ in range(N)]

    def solarr(roww, colm):
        venuss_path = []
        satturn_root = colm

        while jupitr[roww][satturn_root] != satturn_root:
            venuss_path.append(satturn_root)
            satturn_root = jupitr[roww][satturn_root]

        for marsr_pos in venuss_path:
            jupitr[roww][marsr_pos] = satturn_root

        return satturn_root

    for mercurry, marsr, satturn in reversed(earthquakes):
        neptun = satturn * satturn

        for uranus in range(
            mercurry - satturn,
            mercurry + satturn + 1
        ):
            plutto = uranus - mercurry
            earthh = neptun - plutto * plutto
            moonn = __import__("math").isqrt(earthh)

            startt = marsr - moonn
            endd = marsr + moonn

            colm = solarr(uranus, startt)

            while colm <= endd:
                venuss[uranus][colm] = (
                    earthh - (colm - marsr) ** 2 + 1
                )

                jupitr[uranus][colm] = solarr(
                    uranus, colm + 1
                )

                colm = solarr(uranus, colm)

    return venuss


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
