import sys


def read_tokens():
    """Yield whitespace-separated tokens from stdin, one at a time."""
    for line in sys.stdin.buffer:
        yield from line.split()


def main():
    tokens = read_tokens()
    num_tests = int(next(tokens))
    results = []

    for _ in range(num_tests):
        n = int(next(tokens))
        restore_time = int(next(tokens))

        # Slots for the (up to) two charges currently in use.
        # Each entry is the time at which that charge becomes available again.
        first_charge = None
        second_charge = None
        possible = True

        for _ in range(n):
            event_time = int(next(tokens))  # always read all N values

            if not possible:
                continue

            # Free up any charge whose restore time has already passed.
            if first_charge is not None and first_charge <= event_time:
                first_charge = second_charge
                second_charge = None

            if first_charge is not None and second_charge is not None:
                # Both charges are still busy — this event can't be handled.
                possible = False
            elif first_charge is None:
                first_charge = event_time + restore_time
            else:
                second_charge = first_charge + restore_time

        results.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(results) + "\n")


if __name__ == "__main__":
    main()