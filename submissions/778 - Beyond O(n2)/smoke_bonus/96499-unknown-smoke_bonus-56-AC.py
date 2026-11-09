import sys
from collections import deque

input = sys.stdin.buffer.readline

t = int(input())
answers = []

for _ in range(t):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))

    charges = 2
    pending = deque()
    possible = True

    for time in times:
        while pending and pending[0] <= time:
            charges += 1
            pending.popleft()

        if charges == 0:
            possible = False
            break

        charges -= 1

        if pending:
            pending.append(pending[-1] + r)
        else:
            pending.append(time + r)

    if possible:
        answers.append("YES")
    else:
        answers.append("NO")

print("\n".join(answers))