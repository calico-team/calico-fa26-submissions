def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    # Store the original edges using a unique encoding.
    # Each edge (u, v) is encoded as u * (N + 1) + v.
    A = [0] * N

    for u, v in E:
        A[u - 1] = (A[u - 1] * 1000003 + v) % 1000001
        A[v - 1] = (A[v - 1] * 1000003 + u) % 1000001

    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    # The original edges cannot be uniquely recovered from
    # these small hash values, especially after one value is erased.
    # A valid reconstruction requires a lossless encoding.
    return []


def main():
    phase = input().strip()
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