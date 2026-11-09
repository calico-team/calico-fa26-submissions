import sys


def can_fulfill(times, recharge_time):
    charges = 2
    next_recharge = -1

    for time in times:
        # Recharges due now happen before the smoke request.
        while charges < 2 and next_recharge <= time:
            charges += 1
            if charges < 2:
                next_recharge += recharge_time
            else:
                next_recharge = -1

        if charges == 0:
            return False

        if charges == 2:
            # This smoke starts a new recharge.
            next_recharge = time + recharge_time
        charges -= 1

    return True


def main():
    input_stream = sys.stdin.buffer
    first_line = input_stream.readline()
    if not first_line:
        return

    test_cases = int(first_line)
    output = []

    for _ in range(test_cases):
        n, recharge_time = map(int, input_stream.readline().split())
        times = list(map(int, input_stream.readline().split()))
        output.append("YES" if can_fulfill(times, recharge_time) else "NO")

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    main()
