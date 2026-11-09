def read_your_input():
    import sys
    from array import array

    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N = int(input())
        A = [x - 1 for x in map(int, input().split())]
        V = list(map(int, input().split()))

        left = array("i", [0])
        right = array("i", [0])

        def insert(root, val):
            new_root = len(left)
            left.append(left[root])
            right.append(right[root])

            old = root
            cur = new_root

            for b in range(29, -1, -1):
                bit = (val >> b) & 1

                if bit == 0:
                    child = left[old]
                    new_child = len(left)
                    left.append(left[child])
                    right.append(right[child])
                    left[cur] = new_child
                else:
                    child = right[old]
                    new_child = len(left)
                    left.append(left[child])
                    right.append(right[child])
                    right[cur] = new_child

                old = child
                cur = new_child

            return new_root

        def insert_base(root, val):
            cur = root

            for b in range(29, -1, -1):
                bit = (val >> b) & 1

                if bit == 0:
                    if left[cur] == 0:
                        left[cur] = len(left)
                        left.append(0)
                        right.append(0)
                    cur = left[cur]
                else:
                    if right[cur] == 0:
                        right[cur] = len(left)
                        left.append(0)
                        right.append(0)
                    cur = right[cur]

        def maximum(root, val):
            cur = root
            ans = 0

            for b in range(29, -1, -1):
                bit = (val >> b) & 1

                if bit == 0:
                    if right[cur]:
                        ans |= 1 << b
                        cur = right[cur]
                    else:
                        cur = left[cur]
                else:
                    if left[cur]:
                        ans |= 1 << b
                        cur = left[cur]
                    else:
                        cur = right[cur]

            return ans

        indegree = [0] * N

        for x in A:
            indegree[x] += 1

        queue = []
        for i in range(N):
            if indegree[i] == 0:
                queue.append(i)

        removed = []

        for u in queue:
            removed.append(u)
            v = A[u]
            indegree[v] -= 1

            if indegree[v] == 0:
                queue.append(v)

        roots = [0] * N
        tags = [0] * N
        answer = [0] * N

        visited = [False] * N

        for i in range(N):
            if indegree[i] > 0 and not visited[i]:

                cycle = []
                u = i

                while not visited[u]:
                    visited[u] = True
                    cycle.append(u)
                    u = A[u]

                length = len(cycle)

                prefix = [0]
                total = 0

                for u in cycle:
                    total ^= V[u]
                    prefix.append(total)

                base = 0

                for x in prefix[1:]:
                    insert_base(base, x)
                    insert_base(base, x ^ total)

                for j, u in enumerate(cycle):
                    roots[u] = base
                    tags[u] = prefix[j]
                    answer[u] = maximum(base, tags[u])

        for u in reversed(removed):
            v = A[u]

            roots[u] = insert(roots[v], tags[v])
            tags[u] = tags[v] ^ V[u]

            answer[u] = maximum(roots[u], tags[u])

        print(*answer)


read_your_input()
