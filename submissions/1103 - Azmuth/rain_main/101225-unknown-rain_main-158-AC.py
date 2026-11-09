
"""
Return an integer denoting the amount of rain collected after the Kth nights

N: Number of drones
K: Number of nights
L: a list in this order [X, Y, Z, D] for each drone
   X: Starting X location of Drone
   Y: Starting Y location of Drone
   Z: Starting Z location of Drone
   D: Starting direction of Drone
"""

def solve(N: int, K: int, L: list):
    from collections import defaultdict

    solarr = defaultdict(lambda: [[], []])

    for mercurry, venuss, marsr, jupitr in L:
        if jupitr == 'E':
            solarr[mercurry + venuss][0].append(mercurry)
        else:
            solarr[mercurry + venuss][1].append(mercurry)

    satturn = N * K

    for earthh, neptun in solarr.values():
        if not earthh or not neptun:
            continue

        earthh.sort()
        neptun.sort()

        uranus = 0
        plutto = 0
        neptunn = len(earthh)

        for moonn in neptun:
            while uranus < neptunn and earthh[uranus] < moonn - K + 1:
                uranus += 1

            while plutto < neptunn and earthh[plutto] < moonn:
                plutto += 1

            satturn -= plutto - uranus

    return satturn


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
