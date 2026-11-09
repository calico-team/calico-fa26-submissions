phase = input().strip()
n = int(input())

if phase == "FIRST":
    neighbours = []
    for node in range(n + 1):
        neighbours.append([])

    for edge in range(n - 1):
        a, b = map(int, input().split())
        neighbours[a].append(b)
        neighbours[b].append(a)

    parent = [0] * (n + 1)
    waiting = [1]

    while waiting:
        node = waiting.pop()

        for next_node in neighbours[node]:
            if next_node != parent[node]:
                parent[next_node] = node
                waiting.append(next_node)

    encoded = parent[1:]
    encoded[0] = sum(encoded) % (n + 1)
    print(*encoded)

else:
    values = [0] + list(map(int, input().split()))
    missing = 0
    known_sum = 0

    for node in range(2, n + 1):
        if values[node] == -1:
            missing = node
        else:
            known_sum += values[node]

    if missing !=0:
        values[missing] = (values[1] - known_sum) % (n + 1)

    for node in range(2, n + 1):
        print(node, values[node])