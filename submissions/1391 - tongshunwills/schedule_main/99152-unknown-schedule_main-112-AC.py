def main():
    T = int(input())
    for _ in range(T):
        N, M, K = map(int, input().split())
        P = [0] + list(map(int, input().split()))

        children = [[] for _ in range(N + 1)]
        for i in range(1, N + 1):
            children[P[i]].append(i)

        height = [0] * (N + 1)
        order = []
        stack = [0]
        while stack:
            v = stack.pop()
            order.append(v)
            for c in children[v]:
                stack.append(c)
        for v in reversed(order):
            h = 0
            for c in children[v]:
                if height[c] > h:
                    h = height[c]
            height[v] = h + 1

        top = height[0] - 1
        bucket = [[] for _ in range(top + 2)]
        for c in children[0]:
            bucket[height[c]].append(c)

        taken = 0
        for _ in range(M):
            batch = []
            h = top
            while h >= 1 and len(batch) < K:
                while bucket[h] and len(batch) < K:
                    batch.append(bucket[h].pop())
                h -= 1
            if not batch:
                break
            taken += len(batch)
            for v in batch:
                for c in children[v]:
                    bucket[height[c]].append(c)

        print(taken)


main()