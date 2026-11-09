import sys


def phase_one(tokens):
    num_vertices = int(tokens[1])
    if num_vertices == 2:
        print("0 0")
        return

    neighbors = [[] for _ in range(num_vertices + 1)]
    read_pos = 2
    for _ in range(num_vertices - 1):
        end_a = int(tokens[read_pos]); end_b = int(tokens[read_pos + 1])
        read_pos += 2
        neighbors[end_a].append(end_b)
        neighbors[end_b].append(end_a)

    parent_of = [0] * (num_vertices + 1)
    parent_of[num_vertices] = -1
    to_visit = [num_vertices]
    while to_visit:
        node = to_visit.pop()
        for nxt in neighbors[node]:
            if nxt != parent_of[node]:
                parent_of[nxt] = node
                to_visit.append(nxt)

    deg = [len(neighbors[node]) for node in range(num_vertices + 1)]

    code = []
    leaf_ptr = 1
    while deg[leaf_ptr] != 1:
        leaf_ptr += 1
    cur_leaf = leaf_ptr
    for _ in range(num_vertices - 2):
        par = parent_of[cur_leaf]
        code.append(par)
        deg[par] -= 1
        if deg[par] == 1 and par < leaf_ptr:
            cur_leaf = par
        else:
            leaf_ptr += 1
            while deg[leaf_ptr] != 1:
                leaf_ptr += 1
            cur_leaf = leaf_ptr

    output_vals = [label - 1 for label in code]
    check = sum(output_vals) % num_vertices
    output_vals.append(check)
    output_vals.append(0)
    print(" ".join(map(str, output_vals)))


def phase_two(tokens):
    num_vertices = int(tokens[1])
    arr = [int(x) for x in tokens[2:2 + num_vertices]]

    if num_vertices == 2:
        print("1 2")
        return

    erased_idx = arr.index(-1)
    if erased_idx < num_vertices - 2:
        rest_sum = sum(arr[i] for i in range(num_vertices - 2) if i != erased_idx)
        arr[erased_idx] = (arr[num_vertices - 2] - rest_sum) % num_vertices

    code = [arr[i] + 1 for i in range(num_vertices - 2)]

    deg = [1] * (num_vertices + 1)
    for label in code:
        deg[label] += 1

    result_edges = []
    leaf_ptr = 1
    while deg[leaf_ptr] != 1:
        leaf_ptr += 1
    cur_leaf = leaf_ptr
    for label in code:
        result_edges.append((cur_leaf, label))
        deg[label] -= 1
        if deg[label] == 1 and label < leaf_ptr:
            cur_leaf = label
        else:
            leaf_ptr += 1
            while deg[leaf_ptr] != 1:
                leaf_ptr += 1
            cur_leaf = leaf_ptr
    result_edges.append((cur_leaf, num_vertices))

    sys.stdout.write("\n".join(f"{a} {b}" for a, b in result_edges) + "\n")


def main():
    tokens = sys.stdin.read().split()
    if tokens[0] == "FIRST":
        phase_one(tokens)
    else:
        phase_two(tokens)


if __name__ == "__main__":
    main()