
def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.

    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    from collections import deque
    from heapq import heappush, heappop, heapify

    mercurry = [[] for _ in range(N)]
    venuss = [0] * N

    for marsr, jupitr in enumerate(P):
        if jupitr != 0:
            mercurry[jupitr - 1].append(marsr)
            venuss[jupitr - 1] += 1

    satturn = [1] * N
    neptun = deque(
        earthh for earthh in range(N)
        if venuss[earthh] == 0
    )

    while neptun:
        earthh = neptun.popleft()
        solarr = P[earthh] - 1

        if solarr >= 0:
            satturn[solarr] = max(
                satturn[solarr],
                satturn[earthh] + 1
            )

            venuss[solarr] -= 1

            if venuss[solarr] == 0:
                neptun.append(solarr)

    uranus = [
        (-satturn[earthh], earthh)
        for earthh in range(N)
        if P[earthh] == 0
    ]
    heapify(uranus)

    plutto = 0

    for _ in range(min(M, N)):
        if not uranus:
            break

        moonn = []

        for _ in range(min(K, len(uranus))):
            _, earthh = heappop(uranus)
            plutto += 1
            moonn.extend(mercurry[earthh])

        for earthh in moonn:
            heappush(
                uranus,
                (-satturn[earthh], earthh)
            )

    return plutto


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))


if __name__ == '__main__':
    main()
