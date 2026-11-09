# Source: https://usaco.guide/general/io
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
t = data[0]
i = 1
answers = []

for _ in range(t):
    n, r = data[i], data[i + 1]
    i += 2
    times = data[i:i + n]
    i += n

    # Track when the next charge becomes available.
    available = [0, 0]
    possible = True

    for time in times:
        # A charge is ready if its recharge time has passed.
        ready = next((j for j in range(2) if available[j] <= time), None)
        if ready is None:
            possible = False
            break
        available[ready] = time + r

    answers.append("YES" if possible else "NO")

print("\n".join(answers))