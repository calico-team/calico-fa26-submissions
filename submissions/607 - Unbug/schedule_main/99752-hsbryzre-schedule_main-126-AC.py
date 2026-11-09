import sys

def solve(N, M, K, P):
    unlocks = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    
    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            unlocks[p].append(i)
            deg[p] += 1

    priority = [0] * (N + 1)
    leaves = [i for i in range(1, N + 1) if deg[i] == 0]
    
    for u in leaves:
        p = P[u - 1]
        if p != 0:
            if priority[p] < priority[u] + 1:
                priority[p] = priority[u] + 1
            deg[p] -= 1
            if deg[p] == 0:
                leaves.append(p)

    buckets = [[] for _ in range(1005)]
    for i in range(1, N + 1):
        if P[i - 1] == 0:
            buckets[priority[i]].append(i)

    total_taken = 0
    max_p = 1000

    for _ in range(M):
        taken = []
        while max_p >= 0 and len(taken) < K:
            if buckets[max_p]:
                taken.append(buckets[max_p].pop())
            else:
                max_p -= 1

        if not taken:
            break

        total_taken += len(taken)

        for u in taken:
            for next_c in unlocks[u]:
                p = priority[next_c]
                buckets[p].append(next_c)
                if p > max_p:
                    max_p = p

    return total_taken


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    T = int(next(iterator))
    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        K = int(next(iterator))
        P = [int(next(iterator)) for _ in range(N)]
        out.append(str(solve(N, M, K, P)))

    print('\n'.join(out))


if __name__ == '__main__':
    main()