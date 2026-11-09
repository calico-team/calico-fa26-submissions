import sys
from collections import deque


def can_fulfill_all_smoke_requests(number_of_requests, recharge_seconds, request_times):
    remaining_smokes = 2
    recharge_finish_times = deque()

    for request_time in request_times:
        # Process any smoke recharges that finish at or before this request.
        while recharge_finish_times and recharge_finish_times[0] <= request_time:
            recharge_finish_times.popleft()
            remaining_smokes += 1
            if remaining_smokes > 2:
                remaining_smokes = 2

        # No smoke available, so this request cannot be fulfilled.
        if remaining_smokes == 0:
            return "NO"

        # Use one smoke charge.
        remaining_smokes -= 1

        # Schedule when this used smoke will be recharged.
        # If another smoke is already recharging, this one waits behind it.
        if recharge_finish_times:
            finish_time = recharge_finish_times[-1] + recharge_seconds
        else:
            finish_time = request_time + recharge_seconds

        recharge_finish_times.append(finish_time)

    return "YES"


def main():
    input_data = list(map(int, sys.stdin.buffer.read().split()))
    if not input_data:
        return

    test_case_count = input_data[0]
    index = 1
    answers = []

    for _ in range(test_case_count):
        number_of_requests = input_data[index]
        recharge_seconds = input_data[index + 1]
        index += 2

        request_times = input_data[index:index + number_of_requests]
        index += number_of_requests

        answers.append(
            can_fulfill_all_smoke_requests(
                number_of_requests,
                recharge_seconds,
                request_times
            )
        )

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()