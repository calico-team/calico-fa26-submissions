import sys


def can_fulfill(times: list[int], recharge_time: int) -> bool:
    charges = 2
    # When charges < 2, this is the completion time of the currently active
    # recharge. A second recharge cannot begin until this one completes.
    next_recharge = None

    for time in times:
        # Process all recharges completed by this request time. If both
        # charges had been used, the next recharge begins only after the
        # previous one finishes, so advance its completion time by R.
        while charges < 2 and next_recharge is not None and next_recharge <= time:
            charges += 1
            if charges < 2:
                next_recharge += recharge_time
            else:
                next_recharge = None

        if charges == 0:
            return False

        was_full = charges == 2
        charges -= 1
        if was_full:
            # This use leaves one charge, so its recharge starts now.
            next_recharge = time + recharge_time

    return True


def main() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    t = data[0]
    index = 1
    answers = []

    for _ in range(t):
        n, r = data[index], data[index + 1]
        index += 2
        times = data[index:index + n]
        index += n
        answers.append("YES" if can_fulfill(times, r) else "NO")

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()
