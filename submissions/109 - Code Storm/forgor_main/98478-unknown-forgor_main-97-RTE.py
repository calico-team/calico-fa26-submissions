def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
import sys
import heapq

MOD = 200001

def en_tree(n,adj):
    dgree = [len(adj[i]) for i in range(n + 1)]

    leavs = []

    for i in range(1, n+1):
        if degree[i]==1:
            heapq.heappush(leavs, i)

    prufer = []

    for _ in range(n - 2):
        leaf = heapq.heappop(leavs)

def amnesiac(n,arr):
    mis = arr.index(-1)
    prufer = arr[:n-2]


    if mis <n-2:
        checksum = arr[n-2]
        kn_sum = sum(x for x in prufer if x != -1)
        prufer[missing] = (checksum - kn_sum) % MOD

    degre = [1]*(n+1)

    for x in pruffer:
        degree[x] += 1





    return [0] * N


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    return []


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

