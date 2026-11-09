import sys

def solve():
    data = sys.stdin.read().split()
    
    if not data:
        return

    T = int(data[0])
    idx = 1
    out = []

    for _ in range(T):
        N = int(data[idx])
        R = int(data[idx + 1])
        idx += 2

        A = list(map(int, data[idx:idx + N]))
        idx += N

        # Stores when used smoke charges will be ready again
        recharge_times = []
        possible = True

        for t in A:
            # Remove smokes that have finished recharging
            while recharge_times and recharge_times[0] <= t:
                recharge_times.pop(0)

            # If both charges are still recharging, we cannot smoke
            if len(recharge_times) == 2:
                possible = False
                break

            # Schedule the recharge of the smoke we just used
            if recharge_times:
                recharge_times.append(recharge_times[-1] + R)
            else:
                recharge_times.append(t + R)

        if possible:
            out.append("YES")
        else:
            out.append("NO")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
