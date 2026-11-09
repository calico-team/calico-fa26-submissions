import sys


def solve():
    input = sys.stdin.readline

    test_cases = int(input())

    for _ in range(test_cases):
        smoke_requests, recharge_time = map(int, input().split())
        requests = list(map(int, input().split()))

        charges = 2
        next_recharge = 0

        possible = True

        for current_time in requests:

            # Process completed recharges.
            while charges < 2 and next_recharge <= current_time:
                charges += 1
                next_recharge += recharge_time

            # Check if a smoke charge is available.
            if charges == 0:
                possible = False
                break

            # Consume one charge.
            charges -= 1

            # Schedule recharge if necessary.
            if charges == 1:
                next_recharge = current_time + recharge_time

        print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()