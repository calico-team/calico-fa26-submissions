# Source: https://usaco.guide/general/io
import sys

data = list(map(int, sys.stdin.read().split()))
it = iter(data)

t = next(it)
answers = []

for _ in range(t):
    n = next(it)
    r = next(it)
    times = [next(it) for _ in range(n)]

    available = [0, 0]
    possible = True

    for time in times:
        if available[0] <= time:
            available[0] = time + r
        elif available[1] <= time:
            available[1] = time + r
        else:
            possible = False
            break

    answers.append("YES" if possible else "NO")

print("\n".join(answers))