from array import array

def addValue(left, right, root, value):
    node = root

    for bit in range(29, -1, -1):
        b = (value >> bit) & 1

        if b == 0:
            nxt = left[node]
            if nxt == 0:
                nxt = len(left)
                left.append(0)
                right.append(0)
                left[node] = nxt
        else:
            nxt = right[node]
            if nxt == 0:
                nxt = len(left)
                left.append(0)
                right.append(0)
                right[node] = nxt

        node = nxt


def insertVersion(left, right, root, value):
    newRoot = len(left)
    left.append(left[root])
    right.append(right[root])

    newNode = newRoot
    oldNode = root

    for bit in range(29, -1, -1):
        b = (value >> bit) & 1

        if b == 0:
            oldChild = left[oldNode]
        else:
            oldChild = right[oldNode]

        newChild = len(left)
        left.append(left[oldChild])
        right.append(right[oldChild])

        if b == 0:
            left[newNode] = newChild
        else:
            right[newNode] = newChild

        oldNode = oldChild
        newNode = newChild

    return newRoot


def maxXor(left, right, root, value):
    node = root
    result = 0

    for bit in range(29, -1, -1):
        b = (value >> bit) & 1

        if b == 0:
            nxt = right[node]
            if nxt:
                result |= 1 << bit
            else:
                nxt = left[node]
        else:
            nxt = left[node]
            if nxt:
                result |= 1 << bit
            else:
                nxt = right[node]

        node = nxt

    return result

def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    A = [x - 1 for x in A]

    indegree = [0] * N

    for v in A:
        indegree[v] += 1

    queue = [i for i in range(N) if indegree[i] == 0]
    order = []

    for u in queue:
        order.append(u)
        v = A[u]
        indegree[v] -= 1

        if indegree[v] == 0:
            queue.append(v)

    onCycle = [x > 0 for x in indegree]

    component = [-1] * N
    dinosauraus = [0] * N
    visited = [False] * N

    cycleLeft = array('i', [0])
    cycleRight = array('i', [0])
    cycleRoots = []
    cycleXors = []

    for i in range(N):
        if not onCycle[i] or visited[i]:
            continue

        cycle = []
        u = i

        while not visited[u]:
            visited[u] = True
            cycle.append(u)
            u = A[u]

        cycleXor = 0
        for u in cycle:
            cycleXor ^= V[u]

        root = len(cycleLeft)
        cycleLeft.append(0)
        cycleRight.append(0)

        prefix = 0
        cid = len(cycleRoots)

        for u in cycle:
            component[u] = cid
            dinosauraus[u] = prefix

            prefix ^= V[u]
            addValue(cycleLeft, cycleRight, root, prefix)

        cycleRoots.append(root)
        cycleXors.append(cycleXor)

    pathLeft = array('i', [0])
    pathRight = array('i', [0])

    zeroRoot = insertVersion(pathLeft, pathRight, 0, 0)

    pathRoot = [zeroRoot] * N
    pathXor = [0] * N

    for u in reversed(order):
        v = A[u]

        component[u] = component[v]
        dinosauraus[u] = dinosauraus[v]
        pathXor[u] = pathXor[v] ^ V[u]

        pathRoot[u] = insertVersion(
            pathLeft, pathRight, pathRoot[v], pathXor[u]
        )

    answers = [0] * N

    for u in range(N):
        cid = component[u]
        x = pathXor[u] ^ dinosauraus[u]

        cycleBest = max(
            maxXor(cycleLeft, cycleRight, cycleRoots[cid], x),
            maxXor(cycleLeft, cycleRight, cycleRoots[cid], x ^ cycleXors[cid])
        )

        treeBest = 0

        if not onCycle[u]:
            treeBest = maxXor(
                pathLeft, pathRight, pathRoot[A[u]], pathXor[u]
            )

        answers[u] = max(treeBest, cycleBest)

    return answers


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
