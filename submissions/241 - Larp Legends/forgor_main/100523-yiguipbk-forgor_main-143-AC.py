import sys


def compute_bit_layout(node_count):
    # Low bits hold the parent id, high bits hold a slice of the checksum
    parent_bits = node_count.bit_length()
    checksum_bits_per_node = max(1, 19 - parent_bits)
    return parent_bits, checksum_bits_per_node


def encode_tree(tokens, position):
    node_count = int(tokens[position])
    position += 1

    neighbors = [[] for _ in range(node_count + 1)]
    for _ in range(node_count - 1):
        first = int(tokens[position])
        second = int(tokens[position + 1])
        position += 2
        neighbors[first].append(second)
        neighbors[second].append(first)

    # Root the tree at node 1 and record each node's parent
    parent = [0] * (node_count + 1)
    visited = [False] * (node_count + 1)
    visited[1] = True
    to_visit = [1]
    while to_visit:
        current = to_visit.pop()
        for neighbor in neighbors[current]:
            if not visited[neighbor]:
                visited[neighbor] = True
                parent[neighbor] = current
                to_visit.append(neighbor)

    # XOR of all parents, used later to rebuild a missing one
    parent_checksum = 0
    for node in range(2, node_count + 1):
        parent_checksum ^= parent[node]

    parent_bits, checksum_bits_per_node = compute_bit_layout(node_count)

    encoded_values = []
    for node in range(1, node_count + 1):
        encoded = parent[node]
        first_bit_index = (node - 1) * checksum_bits_per_node

        # Spread copies of the checksum bits across every node's high bits
        for offset in range(checksum_bits_per_node):
            checksum_bit = (first_bit_index + offset) % parent_bits
            if (parent_checksum >> checksum_bit) & 1:
                encoded |= 1 << (parent_bits + offset)

        encoded_values.append(encoded)

    print(" ".join(str(value) for value in encoded_values))


def decode_tree(tokens, position):
    node_count = int(tokens[position])
    position += 1

    encoded_values = []
    for offset in range(node_count):
        encoded_values.append(int(tokens[position + offset]))

    parent_bits, checksum_bits_per_node = compute_bit_layout(node_count)
    parent_mask = (1 << parent_bits) - 1

    # The erased entry is marked with -1
    missing_node = encoded_values.index(-1) + 1

    parent = [0] * (node_count + 1)
    for node in range(1, node_count + 1):
        if node != missing_node:
            parent[node] = encoded_values[node - 1] & parent_mask

    # The root has no parent, so only other nodes need rebuilding
    if missing_node != 1:
        checksum_bit_values = [0] * parent_bits
        for node in range(1, node_count + 1):
            if node == missing_node:
                continue
            first_bit_index = (node - 1) * checksum_bits_per_node
            for offset in range(checksum_bits_per_node):
                checksum_bit = (first_bit_index + offset) % parent_bits
                stored_bit = (encoded_values[node - 1] >> (parent_bits + offset)) & 1
                checksum_bit_values[checksum_bit] = stored_bit

        parent_checksum = 0
        for bit_index in range(parent_bits):
            if checksum_bit_values[bit_index]:
                parent_checksum |= 1 << bit_index

        # XOR out every known parent, what remains is the missing one
        recovered_parent = parent_checksum
        for node in range(2, node_count + 1):
            if node != missing_node:
                recovered_parent ^= parent[node]
        parent[missing_node] = recovered_parent

    edge_lines = []
    for node in range(2, node_count + 1):
        edge_lines.append("%d %d" % (node, parent[node]))
    print("\n".join(edge_lines))


def main():
    tokens = sys.stdin.buffer.read().split()
    if tokens[0] == b"FIRST":
        encode_tree(tokens, 1)
    else:
        decode_tree(tokens, 1)


main()