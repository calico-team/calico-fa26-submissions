import sys
import heapq

data = list(map(int, sys.stdin.buffer.read().split()))

idx = 0

n, m, k = data[idx:idx + 3]
idx += 3

p = data[idx:idx + n]

children = [[] for _ in range(n)]
roots = []

for i in range(n):
    if p[i] == 0:
        roots.append(i)
    else:
        children[p[i] - 1].append(i)

order = roots[:]

for node in order:
    for child in children[node]:
        order.append(child)

height = [1] * n

for node in reversed(order):
    for child in children[node]:
        height[node] = max(height[node], height[child] + 1)

available = []

for node in roots:
    heapq.heappush(available, (-height[node], node))

answer = 0

for semester in range(m):
    selected = []

    for i in range(k):
        if not available:
            break

        course = heapq.heappop(available)[1]
        selected.append(course)

    answer += len(selected)

    for course in selected:
        for child in children[course]:
            heapq.heappush(available, (-height[child], child))

print(answer)