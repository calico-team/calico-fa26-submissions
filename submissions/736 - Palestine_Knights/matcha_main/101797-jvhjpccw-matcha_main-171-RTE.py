def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    if N == 1:
        return R[0]

    fixed = 0
    variable = []

    for low, high in zip(L, R):
        if low == high:
            fixed ^= low
        else:
            variable.append((low, high))

    if not variable:
        return fixed

    if len(variable) == 1:
        low, high = variable[0]

        if high - low <= 10000:
            return max(fixed ^ x for x in range(low, high + 1))

    raise NotImplementedError(
        "General interval XOR optimization required"
    )

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
