def solve():
    test_cases = int(input())

    for _ in range(test_cases):
        n, semesters, limit = map(int, input().split())
        prerequisites = [0] + list(map(int, input().split()))

        tree = [[] for _ in range(n + 1)]
        roots = []

        for course in range(1, n + 1):
            parent = prerequisites[course]

            if parent == 0:
                roots.append(course)
            else:
                tree[parent].append(course)

        order = []
        stack = roots[:]

        while stack:
            node = stack.pop()
            order.append(node)
            stack.extend(tree[node])

        weight = [1] * (n + 1)

        for node in reversed(order):
            for nxt in tree[node]:
                weight[node] += weight[nxt]

        buckets = [[] for _ in range(n + 1)]
        active = 0

        for root in roots:
            size = weight[root]
            buckets[size].append(root)
            active |= 1 << size

        answer = 0

        for _ in range(semesters):
            if active == 0:
                break

            selected = []

            for _ in range(limit):
                if active == 0:
                    break

                size = active.bit_length() - 1
                node = buckets[size].pop()

                if not buckets[size]:
                    active ^= 1 << size

                selected.append(node)
                answer += 1

            for node in selected:
                for nxt in tree[node]:
                    size = weight[nxt]
                    buckets[size].append(nxt)
                    active |= 1 << size

        print(answer)


solve()
