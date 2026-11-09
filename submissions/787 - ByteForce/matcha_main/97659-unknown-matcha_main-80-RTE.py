def solve(N: int, L: list[int], R: list[int]) -> int:
    max_xor = 0

    for b in range(29, -1, -1):
        flexible_idx = -1
        fixed_ones = 0

        for i in range(N):
            if (L[i] >> b) != (R[i] >> b):
                flexible_idx = i
            else:
                if (L[i] >> b) & 1:
                    fixed_ones += 1

        if flexible_idx != -1:
            max_xor |= 1 << b
            L[flexible_idx] = 0
            R[flexible_idx] = (1 << b) - 1
        else:
            if fixed_ones % 2 != 0:
                max_xor |= 1 << b

    return max_xor


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))


if _name_ == '_main_':
    main()
