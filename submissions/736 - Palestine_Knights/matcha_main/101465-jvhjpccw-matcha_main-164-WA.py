def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    fixed_xor = 0
    flexible_mask = 0

    for low, high in zip(L, R):
        difference = low ^ high

        if difference == 0:
            fixed_xor ^= low
        else:
            bit = difference.bit_length()
            mask = (1 << bit) - 1

            fixed_xor ^= low & ~mask
            flexible_mask |= mask

    return fixed_xor | flexible_mask

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
