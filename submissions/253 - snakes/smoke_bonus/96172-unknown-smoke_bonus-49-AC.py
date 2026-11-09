import sys

def solve(n, r, times):
    charges = 2
    ready = 0  # when the recharging smoke comes back
    for t in times:
        # recharges land before requests on the same second
        while charges < 2 and ready <= t:
            charges += 1
            ready += r
        if charges == 0:
            return "NO"
        if charges == 2:
            ready = t + r
        charges -= 1
    return "YES"

data = sys.stdin.buffer.read().split()
idx = 0
T = int(data[idx]); idx += 1
out = []
for _ in range(T):
    n = int(data[idx]); r = int(data[idx + 1]); idx += 2
    times = map(int, data[idx:idx + n]); idx += n
    out.append(solve(n, r, times))
print("\n".join(out))
