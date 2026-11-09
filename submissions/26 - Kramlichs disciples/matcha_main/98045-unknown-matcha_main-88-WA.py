def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    if N == 1:
        return R[0]

    basis = [0] * 30

    def add(value: int) -> None:
        for bit in range(29, -1, -1):
            if not value >> bit & 1:
                continue
            if basis[bit]:
                value ^= basis[bit]
            else:
                basis[bit] = value
                return

    def maximum(value: int) -> int:
        result = value
        for bit in range(29, -1, -1):
            result = max(result, result ^ basis[bit])
        return result

    for lower, upper in zip(L, R):
        add(lower ^ upper)

    answer = maximum(0)
    for lower, upper in zip(L, R):
        candidates = {lower, upper}
        if upper - lower <= 64:
            candidates.update(range(lower, upper + 1))
        else:
            for bit in range(30):
                step = 1 << bit
                candidates.add(lower + step)
                candidates.add(upper - step)
        for value in candidates:
            if lower <= value <= upper:
                answer = max(answer, maximum(value))
    return answer

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
