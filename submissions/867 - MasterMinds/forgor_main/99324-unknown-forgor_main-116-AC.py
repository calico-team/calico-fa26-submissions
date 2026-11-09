import sys


def main():
    tokens = sys.stdin.read().split()
    phase = tokens[0]
    no_vertices = int(tokens[1])

    if phase == "FIRST":
        neighbors = [[] for _ in range(no_vertices + 1)]
        degree = [0] * (no_vertices + 2)
        index = 2
        for _ in range(no_vertices - 1):
            a_node = int(tokens[index]); b_node = int(tokens[index + 1]); index += 2
            neighbors[a_node].append(b_node)
            neighbors[b_node].append(a_node)
            degree[a_node] += 1
            degree[b_node] += 1
        parent = [0] * (no_vertices + 1)
        seen = [False] * (no_vertices + 1)
        seen[no_vertices] = True
        stack = [no_vertices]
        while stack:
            x = stack.pop()
            for y in neighbors[x]:
                if not seen[y]:
                    seen[y] = True
                    parent[y] = x
                    stack.append(y)
        seq = []
        smallest = 1
        while degree[smallest] != 1:
            smallest += 1
        leaf = smallest
        for _ in range(no_vertices - 2):
            next_node = parent[leaf]
            seq.append(next_node)
            degree[leaf] = 0
            degree[next_node] -= 1
            if degree[next_node] == 1 and next_node < smallest:
                leaf = next_node
            else:
                while degree[smallest] != 1:
                    smallest += 1
                leaf = smallest

        checksum = 0
        for x in seq:
            checksum ^= x

        result = seq + [checksum, 0]
        print(" ".join(map(str, result)))

    else:
        received = [int(x) for x in tokens[2:2 + no_vertices]]
        seq = received[:no_vertices - 2]
        checksum = received[no_vertices - 2]

        if -1 in seq:
            missing_pos = seq.index(-1)
            missing_value = checksum
            for i, x in enumerate(seq):
                if i != missing_pos:
                    missing_value ^= x
            seq[missing_pos] = missing_value

        degree = [1] * (no_vertices + 2)
        for x in seq:
            degree[x] += 1

        out = []
        smallest = 1
        while degree[smallest] != 1:
            smallest += 1
        leaf = smallest
        for v in seq:
            out.append(f"{leaf} {v}")
            degree[leaf] = 0
            degree[v] -= 1
            if degree[v] == 1 and v < smallest:
                leaf = v
            else:
                while degree[smallest] != 1:
                    smallest += 1
                leaf = smallest
        out.append(f"{leaf} {no_vertices}")
        print("\n".join(out))
main()