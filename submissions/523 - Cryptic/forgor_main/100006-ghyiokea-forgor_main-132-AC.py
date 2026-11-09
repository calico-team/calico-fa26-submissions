import heapq

why_did_it_have_to_be_prufer_sequence_so_peak_bro = input().strip()

N = int(input())

if why_did_it_have_to_be_prufer_sequence_so_peak_bro == "FIRST":

    adjacent = [[] for _ in range(N + 1)]

    degree = [0] * (N + 1)

    for _ in range(N - 1):
        u, v = list(map(int, input().split()))

        adjacent[u].append(v)
        adjacent[v].append(u)

        degree[u] += 1
        degree[v] += 1

    leaves = [i for i in range(1, N + 1) if degree[i] == 1]
    heapq.heapify(leaves)

    out = []

    for _ in range(N - 2):

        leaf = heapq.heappop(leaves)

        for v in adjacent[leaf]:

            if degree[v] > 0:
                neighbour = v
                break

        out.append(neighbour)

        degree[neighbour] -= 1

        degree[leaf] = 0


        if degree[neighbour] == 1:

            heapq.heappush(leaves, neighbour)

    checksum = sum(out) % 1000000

    print(" ".join(map(str, out + [checksum, 0])))




if why_did_it_have_to_be_prufer_sequence_so_peak_bro == "SECOND":

    A = list(map(int, input().split()))
    checksum = A[N - 2]

    sequence = A[:N - 2]



    for i in range(N - 2):

        if sequence[i] == -1:
            sequence[i] = (checksum - sum([x for x in sequence if x != -1])) % 1000000
            break

    degree = [1] * (N + 1)

    for x in sequence:
        degree[x] += 1

    leaves = [i for i in range(1, N + 1) if degree[i] == 1]
    heapq.heapify(leaves)

    for x in sequence:
        leaf = heapq.heappop(leaves)

        print(leaf, x)

        degree[x] -= 1
        degree[leaf] -= 1


        if degree[x] == 1:
            heapq.heappush(leaves, x)

    u = heapq.heappop(leaves)

    v = heapq.heappop(leaves)

    print(u, v)
