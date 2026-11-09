import sys

bits = 30


# binary trie that finds the max xor with a number
class XorTrie:
    def __init__(self):
        # node 0 is the root and 0 also means no child
        self.children = [[0, 0]]
        # how many stored numbers go through each node
        self.pass_count = [0]

    def new_node(self):
        self.children.append([0, 0])
        self.pass_count.append(0)
        return len(self.children) - 1

    def update(self, number, change):
        node = 0
        self.pass_count[node] += change
        for bit_position in range(bits - 1, -1, -1):
            bit = (number >> bit_position) & 1
            if self.children[node][bit] == 0:
                self.children[node][bit] = self.new_node()
            node = self.children[node][bit]
            self.pass_count[node] += change

    def add(self, number):
        self.update(number, +1)

    def remove(self, number):
        self.update(number, -1)

    def max_xor_with(self, number):
        node = 0
        best = 0
        for bit_position in range(bits - 1, -1, -1):
            bit = (number >> bit_position) & 1
            # going the opposite way sets this bit of the xor
            wanted_child = self.children[node][1 - bit]
            if wanted_child != 0 and self.pass_count[wanted_child] > 0:
                best |= 1 << bit_position
                node = wanted_child
            else:
                node = self.children[node][bit]
        return best


# each word points to one word so the graph is cycles with trees on them
def find_cycles(word_count, next_word):
    unvisited, in_current_walk, finished = 0, 1, 2
    status = [unvisited] * word_count
    is_on_cycle = [False] * word_count
    cycles = []

    for start in range(word_count):
        if status[start] != unvisited:
            continue

        walk = []
        word = start
        while status[word] == unvisited:
            status[word] = in_current_walk
            walk.append(word)
            word = next_word[word]

        # we hit our own walk so this is a new cycle
        if status[word] == in_current_walk:
            cycle = walk[walk.index(word):]
            for cycle_word in cycle:
                is_on_cycle[cycle_word] = True
            cycles.append(cycle)

        for walked_word in walk:
            status[walked_word] = finished

    return cycles, is_on_cycle


def solve_test_case(word_count, next_word, value):
    cycles, is_on_cycle = find_cycles(word_count, next_word)

    # tree words that point straight to each word
    tree_words_pointing_to = [[] for _ in range(word_count)]
    for word in range(word_count):
        if not is_on_cycle[word]:
            tree_words_pointing_to[next_word[word]].append(word)

    answer = [0] * word_count

    # stopping just before a later word p gives key[word] ^ key[p]
    key = [0] * word_count

    for cycle in cycles:
        # prefix_xor[k] is the xor of the cycle values up to k
        prefix_xor = []
        running_xor = 0
        for cycle_word in cycle:
            running_xor ^= value[cycle_word]
            prefix_xor.append(running_xor)
        full_lap_xor = running_xor

        # all stopping points on the cycle
        # the full lap version covers going around again
        trie = XorTrie()
        for prefix in prefix_xor:
            trie.add(prefix)
            trie.add(prefix ^ full_lap_xor)

        for position, entry_word in enumerate(cycle):
            entry_offset = prefix_xor[position - 1] if position > 0 else 0
            key[entry_word] = entry_offset
            answer[entry_word] = trie.max_xor_with(entry_offset)

            # walk the tree that leads into entry_word
            # the trie holds the cycle values plus the keys on the path to the cycle
            trie.add(key[entry_word])
            # stack items are a word and the next child to visit
            stack = [(entry_word, 0)]
            while stack:
                word, child_index = stack[-1]
                children = tree_words_pointing_to[word]

                if child_index == len(children):
                    # done with this word so take its key out
                    trie.remove(key[word])
                    stack.pop()
                    continue

                stack[-1] = (word, child_index + 1)
                child = children[child_index]
                key[child] = value[child] ^ key[word]
                answer[child] = trie.max_xor_with(key[child])
                trie.add(key[child])
                stack.append((child, 0))

    return answer


def main():
    data = sys.stdin.buffer.read().split()
    position = 0

    test_count = int(data[position])
    position += 1

    output_lines = []
    for _ in range(test_count):
        word_count = int(data[position])
        position += 1

        # words are 0 based here
        next_word = [int(x) - 1 for x in data[position:position + word_count]]
        position += word_count

        value = [int(x) for x in data[position:position + word_count]]
        position += word_count

        answer = solve_test_case(word_count, next_word, value)
        output_lines.append(" ".join(map(str, answer)))

    print("\n".join(output_lines))


if __name__ == "__main__":
    main()