import sys


def compute_depths(node_count, parent_of):
    # depth[v] is the distance from v to the root, where the root itself has depth 1
    depth = [0] * (node_count + 1)

    for start_node in range(1, node_count + 1):
        if depth[start_node] != 0:
            continue

        # Walk upward until we hit the root or a node whose depth is already known
        unresolved_path = []
        current = start_node
        while current != 0 and depth[current] == 0:
            unresolved_path.append(current)
            current = parent_of[current - 1]

        if current == 0:
            known_depth = 0
        else:
            known_depth = depth[current]

        # Fill in depths going back down the path
        while unresolved_path:
            known_depth += 1
            node = unresolved_path.pop()
            depth[node] = known_depth

    return depth


def solve(node_count, level_limit, per_level_capacity, parent_of):
    depth = compute_depths(node_count, parent_of)

    deepest_level = max(depth[1:])

    # Count how many nodes sit at each depth
    nodes_at_depth = [0] * (deepest_level + 2)
    for node in range(1, node_count + 1):
        nodes_at_depth[depth[node]] += 1

    answer = 0
    nodes_above = 0
    tightest_limit = None

    for level in range(1, deepest_level + 1):
        limit_from_this_level = per_level_capacity * (level_limit - level + 1) + nodes_above

        if tightest_limit is None or limit_from_this_level < tightest_limit:
            tightest_limit = limit_from_this_level

        room_left = tightest_limit - nodes_above

        # Not enough room for every node on this level, so we stop here
        if room_left < nodes_at_depth[level]:
            return answer + max(room_left, 0)

        answer += nodes_at_depth[level]
        nodes_above += nodes_at_depth[level]

    return answer


def main():
    tokens = sys.stdin.buffer.read().split()
    position = 0

    test_count = int(tokens[position])
    position += 1

    results = []
    for _ in range(test_count):
        node_count = int(tokens[position])
        level_limit = int(tokens[position + 1])
        per_level_capacity = int(tokens[position + 2])
        position += 3

        parent_of = []
        for offset in range(node_count):
            parent_of.append(int(tokens[position + offset]))
        position += node_count

        results.append(str(solve(node_count, level_limit, per_level_capacity, parent_of)))

    print("\n".join(results))


main()