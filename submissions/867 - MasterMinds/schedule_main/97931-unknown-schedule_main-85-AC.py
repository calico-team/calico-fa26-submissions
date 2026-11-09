import sys
import heapq

def main():
    data = sys.stdin.read().split()
    pos = 0
    Test_Case = int(data[pos]); pos += 1
    out = []

    for _ in range(Test_Case):
        No_course = int(data[pos]); No_semester = int(data[pos + 1]); K = int(data[pos + 2])
        pos += 3
        P = [0] + [int(x) for x in data[pos:pos + No_course]]
        pos += No_course
        children = [[] for _ in range(No_course + 1)]
        roots = []
        for i in range(1, No_course + 1):
            if P[i] == 0:
                roots.append(i)
            else:
                children[P[i]].append(i)

        order = []
        stack = list(roots)
        while stack:
            v = stack.pop()
            order.append(v)
            stack.extend(children[v])

        height = [1] * (No_course + 1)
        for v in reversed(order):
            if P[v] != 0:
                if height[v] + 1 > height[P[v]]:
                    height[P[v]] = height[v] + 1
        heap = [(-height[r], r) for r in roots]
        heapq.heapify(heap)

        taken = 0
        for _ in range(No_semester):
            if not heap:
                break
            chosen = []
            while heap and len(chosen) < K:
                chosen.append(heapq.heappop(heap)[1])
            taken += len(chosen)
            for v in chosen:
                for c in children[v]:
                    heapq.heappush(heap, (-height[c], c))

        out.append(str(taken))

    print("\n".join(out))

main()