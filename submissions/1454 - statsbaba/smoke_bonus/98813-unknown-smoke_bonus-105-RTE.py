import sys
from collections import deque


def can_fulfill_all_requests(number_of_requests, recharge_seconds, request_times):
    available_smokes = 2
    recharge_finish_times = deque()

    for request_time in request_times:
        # Recharges complete before requests at the same timestamp.
        while recharge_finish_times and recharge_finish_times[0] <= request_time:
            recharge_finish_times.popleft()
            available_smokes += 1

        # No smoke charge available for this request.
        if available_smokes == 0:
            return "NO"

        # Use one smoke charge.
        available_smokes -= 1

        # Schedule when this used smoke will become available again.
        # If another smoke is already recharging, this one waits its turn.
        if recharge_finish_times:
            next_finish_time = recharge_finish_times[-1] + recharge_seconds
        else:
            next_finish_time = request_time + recharge_seconds

        recharge_finish_times.append(next_finish_time)

    return "YES"


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    test_case_count = data[0]
    position = 1
    answers = []

    for _ in range(test_case_count):
        number_of_requests = data[position]
        recharge_seconds = data[position + 1]
        position += 2

        request_times = data[position:position + number_of_requests]
        position += number_of_requests

        answers.append(
            can_fulfill_all_requests(
                number_of_requests,
                recharge_seconds,
                request_times
            )
        )

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()