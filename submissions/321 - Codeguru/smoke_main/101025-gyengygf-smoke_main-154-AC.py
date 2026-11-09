import sys
from collections import deque


def can_complete_charges(n, recharge_time, charge_times):
    """
    Determine if all charge uses can be satisfied with 2 chargers.

    Each charger, once used, takes `recharge_time` to become available again.
    A charge used at time t frees up its charger at t + recharge_time.

    Returns "YES" if all charges can be served, otherwise "NO".
    """
    # Chargers currently recharging: stores the time each becomes available.
    # Sorted by availability time (earliest first).
    recharging = deque()

    for t in charge_times:
        # Free up any chargers that have finished recharging by time t.
        while recharging and recharging[0] <= t:
            recharging.popleft()

        # If both chargers are still busy, we can't serve this charge.
        if len(recharging) == 2:
            return "NO"

        if not recharging:
            # Both chargers are free — use one, it's back at t + recharge_time.
            recharging.append(t + recharge_time)
        else:
            # One charger is free, one is busy.
            # Use the free charger, but it can only start recharging
            # after the currently busy one is restored.
            recharging.append(recharging[0] + recharge_time)

    return "YES"


def main():
    data = sys.stdin.read().split()
    idx = 0
    test_cases = int(data[idx]); idx += 1
    results = []

    for _ in range(test_cases):
        n = int(data[idx])
        recharge_time = int(data[idx + 1])
        idx += 2

        charge_times = list(map(int, data[idx:idx + n]))
        idx += n

        results.append(can_complete_charges(n, recharge_time, charge_times))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    main()