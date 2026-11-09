# Source: https://usaco.guide/general/io
import sys


def can_fulfill(times: list[int], recharge_time: int) -> bool:
    charges = 2
    next_recharge = None

    for time in times:
        # Finish any recharges completed by this request.
        while (
            charges < 2
            and next_recharge is not None
            and next_recharge <= time
        ):
            charges += 1
            if charges < 2:
                # The second recharge starts only after the first completes.
                next_recharge += recharge_time
            else:
                next_recharge = None

        if charges == 0:
            return False

        was_full = charges == 2
        charges -= 1

        
        if was_full:
            next_recharge = time + recharge_time

    return True


def main() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    test_cases = data[0]
    index = 1
    answers = []

    for _ in range(test_cases):
        n, recharge_time = data[index], data[index + 1]
        index += 2
        times = data[index:index + n]
        index += n

        answers.append(
            "YES" if can_fulfill(times, recharge_time) else "NO"
        )

    print("\n".join(answers))


if __name__ == "__main__":
    main()

