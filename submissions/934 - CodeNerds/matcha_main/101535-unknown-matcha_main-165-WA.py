
def solve(N: int, L: list[int], R: list[int]) -> int:
    intervals = [[L[i], R[i], 0] for i in range(N)]
    ans = 0

    for b in range(29, -1, -1):

        def get_choices(interval, bit):
            l, r, state = interval
            lb = (l >> bit) & 1
            rb = (r >> bit) & 1

            if state == 0:
                if lb == rb:
                    return [(lb, 0)]
                return [(0, 1), (1, 2)]

            if state == 1:
                if lb == 1:
                    return [(1, 1)]
                return [(0, 1), (1, 3)]

            if state == 2:
                if rb == 0:
                    return [(0, 2)]
                return [(0, 3), (1, 2)]

            return [(0, 3), (1, 3)]

        fixed_sum = 0
        flexible = []

        for interval in intervals:
            choices = get_choices(interval, b)

            if len(choices) == 1:
                fixed_sum ^= choices[0][0]
            else:
                flexible.append(choices)

        assignments = [0] * len(flexible)
        current_sum = fixed_sum

        for choices in flexible:
            current_sum ^= choices[0][0]

        chosen_bit = current_sum

        if chosen_bit == 0 and flexible:
            for i, choices in enumerate(flexible):
                if choices[0][0] != choices[1][0]:
                    assignments[i] = 1
                    chosen_bit = 1
                    break

        if chosen_bit:
            ans |= (1 << b)

        new_intervals = []
        flex_idx = 0

        for interval in intervals:
            choices = get_choices(interval, b)

            if len(choices) == 1:
                new_intervals.append(
                    [interval[0], interval[1], choices[0][1]]
                )
            else:
                selected = choices[assignments[flex_idx]]
                new_intervals.append(
                    [interval[0], interval[1], selected[1]]
                )
                flex_idx += 1

        intervals = new_intervals

    return ans


def main():
    import sys

    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))

        print(solve(N, L, R))


if __name__ == '__main__':
    main()
