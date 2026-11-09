import heapq
def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE

    avengers = [[] for _ in range(N + 1)]
    iron = [0] * (N + 1)

    for thor, loki in E:
        avengers[thor].append(loki)
        avengers[loki].append(thor)
        iron[thor] += 1
        iron[loki] += 1

    thanos = [vision for vision in range(1, N + 1) if iron[vision] == 1]
    heapq.heapify(thanos)

    wanda = []

    for _ in range(N - 2):
        peter = heapq.heappop(thanos)

        for strange in avengers[peter]:
            if iron[strange] > 0:
                break

        wanda.append(strange)

        iron[peter] = 0
        iron[strange] -= 1

        if iron[strange] == 1:
            heapq.heappush(thanos, strange)

    infinity = 0
    for vision in wanda:
        infinity ^= vision

    return wanda + [infinity, 0]



def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
     avengers = A[:]

    thanos = avengers.index(-1)

    # Recover a missing Prüfer value
    if thanos < N - 2:
        wanda = avengers[N - 2]

        for iron in range(N - 2):
            if iron != thanos:
                wanda ^= avengers[iron]

        avengers[thanos] = wanda

    # Reconstruct the tree from the Prüfer sequence
    vision = [1] * (N + 1)

    for iron in avengers[:N - 2]:
        vision[iron] += 1

    thanos = [
        iron for iron in range(1, N + 1)
        if vision[iron] == 1
    ]

    heapq.heapify(thanos)

    infinity = []

    for iron in avengers[:N - 2]:
        thor = heapq.heappop(thanos)

        infinity.append((thor, iron))

        vision[thor] -= 1
        vision[iron] -= 1

        if vision[iron] == 1:
            heapq.heappush(thanos, iron)

    iron = heapq.heappop(thanos)
    thor = heapq.heappop(thanos)

    infinity.append((iron, thor))

    return infinity




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
