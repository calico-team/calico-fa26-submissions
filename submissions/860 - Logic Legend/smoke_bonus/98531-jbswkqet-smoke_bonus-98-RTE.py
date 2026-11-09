import sys


def can_fulfill(times, recharge_time):
    charges = 2
    next_recharge = None

    for time in times:
        # Recharges at this timestamp happen before the request.
        while charges < 2 and next_recharge is not None and next_recharge <= time:
            charges += 1
            if charges < 2:
                # The second recharge starts after the first completes.
                next_recharge += recharge_time
            else:
                next_recharge = None

        if charges == 0:
            return False

        had_two_charges = charges == 2
        charges -= 1

        if had_two_charges:
            next_recharge = time + recharge_time

    return True


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    test_cases = data[0]
    index = 1
    answers = []

    for _ in range(test_cases):
        n = data[index]
        recharge_time = data[index + 1]
        index += 2

        times = data[index:index + n]
        index += n

        if can_fulfill(times, recharge_time):
            answers.append("YES")
        else:
            answers.append("NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()
