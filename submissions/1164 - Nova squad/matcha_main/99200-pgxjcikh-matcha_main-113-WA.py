import sys

def solve():
    data = sys.stdin.read().split()
    if not data:
        return

    pos = 0
    t = int(data[pos])
    pos += 1

    results = []

    for _ in range(t):
        n = int(data[pos])
        pos += 1

        left = list(map(int, data[pos:pos + n]))
        pos += n

        right = list(map(int, data[pos:pos + n]))
        pos += n

        fixed_xor = 0
        free_bit = -1
        intervals = []

        for i in range(n):
            low = left[i]
            high = right[i]

            if low == high:
                fixed_xor ^= low
            else:
                diff = low ^ high
                highest_bit = diff.bit_length() - 1

                mask = ~((1 << (highest_bit + 1)) - 1)
                fixed_xor ^= (low & mask)

                intervals.append((highest_bit, low, high))

        if not intervals:
            results.append(str(fixed_xor))
            continue

        for highest_bit, low, high in intervals:
            free_bit = max(free_bit, highest_bit - 1)

        dp = {tuple([0] * len(intervals)): 0}

        for bit in range(29, -1, -1):

            if bit <= free_bit:
                for state in list(dp.keys()):
                    dp[state] |= (1 << (bit + 1)) - 1
                break

            new_dp = {}
            bit_value = 1 << bit

            for state, current_xor in dp.items():
                choices = []

                for i, status in enumerate(state):
                    highest_bit, low, high = intervals[i]

                    if bit > highest_bit:
                        choices.append([(0, 0)])
                        continue

                    low_bit = (low >> bit) & 1
                    high_bit = (high >> bit) & 1

                    options = []

                    if status == 0:
                        if low_bit == high_bit:
                            options.append((low_bit, 0))
                        else:
                            options.append((0, 2))
                            options.append((1, 1))

                    elif status == 1:
                        if high_bit == 1:
                            options.append((0, 3))
                            options.append((1, 1))
                        else:
                            options.append((0, 1))

                    elif status == 2:
                        if low_bit == 0:
                            options.append((1, 3))
                            options.append((0, 2))
                        else:
                            options.append((1, 2))

                    elif status == 3:
                        options.append((0, 3))
                        options.append((1, 3))

                    choices.append(options)

                def generate(index, xor_value, next_state):
                    if index == len(intervals):
                        new_state = tuple(next_state)
                        result = current_xor | (xor_value << bit)

                        if result > new_dp.get(new_state, -1):
                            new_dp[new_state] = result

                        return

                    for chosen_bit, next_status in choices[index]:
                        next_state.append(next_status)
                        generate(index + 1, xor_value ^ chosen_bit, next_state)
                        next_state.pop()

                generate(0, 0, [])

            pruned = {}

            for state, value in new_dp.items():
                if 3 in state:
                    if -1 not in pruned or value > pruned[-1]:
                        pruned[-1] = value
                        free_bit = max(free_bit, bit - 1)
                else:
                    if state not in pruned or value > pruned[state]:
                        pruned[state] = value

            dp = {}

            for state, value in pruned.items():
                if state == -1:
                    dp[(3,)] = value
                else:
                    dp[state] = value

        answer = max(dp.values()) ^ fixed_xor
        results.append(str(answer))

    print('\n'.join(results))


if __name__ == "__main__":
    solve()