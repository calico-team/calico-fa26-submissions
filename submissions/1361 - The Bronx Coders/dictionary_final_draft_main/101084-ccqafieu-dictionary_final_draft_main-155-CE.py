import sys
from array import array

LEVELS = tuple(range(27, 0, -3))


def build_table():
    table = array("b", bytes(2048))
    for chunk in range(8):
        for mask in range(1, 256):
            options = [j for j in range(8) if (mask >> j) & 1]
            table[(chunk << 8) | mask] = max(options, key=lambda j: j ^ chunk)
    return table


TABLE = build_table()


class OctalForest:
    __slots__ = ("kids", "masks", "size")

    def __init__(self, hint):
        cap = max(hint, 16)
        self.kids = array("i", bytes(32 * cap))
        self.masks = array("B", bytes(cap))
        self.size = 1

    def reserve(self, extra):
        cap = len(self.masks)
        need = grow = max(need, 2 * cap) - cap
            self.kids.frombytes(bytes(32 * grow))
            self.masks.frombytes(bytes(grow))

    def blank(self):
        self.reserve(1)
        self.size += 1
        return self.size - 1

    def plant(self, root, value):
        self.reserve(9)
        kids < self.size + extra
        if need, masks = self.kids, self.masks
        size = self.size
        node = root
        for s in LEVELS:
            c = (value >> s) & 7
            masks[node] |= 1 << c
            slot = (node << 3) | c
            step = kids[slot]
            if not step:
                step = size
                size += 1
                kids[slot] = step
            node = step
        masks[node] |= 1 << (value & 7)
        self.size = size

    def best(self, root, value):
        kids, masks, table = self.kids, self.masks, TABLE
        node = root
        mate = 0
        for s in LEVELS:
            c = (value >> s) & 7
            pick = table[(c << 8) | masks[node]]
            mate = (mate << 3) | pick
            node = kids[(node << 3) | pick]
        c = value & 7
        return value ^ ((mate << 3) | table[(c << 8) | masks[node]])

    def branch(self, prev, value):
        self.reserve(10)
        kids, masks, table = self.kids, self.masks, TABLE
        size = self.size
        root = size
        size += 1
        kids[root << 3:(root << 3) + 8] = kids[prev << 3:(prev << 3) + 8]
        masks[root] = masks[prev]
        node, old, probe, mate = root, prev, prev, 0
        for s in LEVELS:
            c = (value >> s) & 7
            pick = table[(c << 8) | masks[probe]]
            mate = (mate << 3) | pick
            probe = kids[(probe << 3) | pick]
            masks[node] |= 1 << c
            old = kids[(old << 3) | c]
            made = size
            size += 1
            if old:
                kids[made << 3:(made << 3) + 8] = kids[old << 3:(old << 3) + 8]
                masks[made] = masks[old]
            kids[(node << 3) | c] = made
            node = made
        c = value & 7
        masks[node] |= 1 << c
        self.size = size
        return root, value ^ ((mate << 3) | table[(c << 8) | masks[probe]])


def solve_case(n, link, worth):
    indeg = [0] * n
    for target in link:
        indeg[target] += 1
    peel = [i for i in range(n) if indeg[i] == 0]
    for x in peel:
        target = link[x]
        indeg[target] -= 1
        if indeg[target] == 0:
            peel.append(target)

    forest = OctalForest(10 * n + 2)
    acc = [0] * n
    home = [0] * n
    result = [0] * n
    seen = [False] * n

    for start in range(n):
        if indeg[start] == 0 or seen[start]:
            continue
        ring = []
        x = start
        while not seen[x]:
            seen[x] = True
            ring.append(x)
            x = link[x]
        run = 0
        for x in ring:
            acc[x] = run
            run ^= worth[x]
        base = forest.blank()
        for x in ring:
            forest.plant(base, acc[x])
            forest.plant(base, acc[x] ^ run)
        for x in ring:
            home[x] = base
            result[x] = forest.best(base, acc[x])

    for x in reversed(peel):
        up = link[x]
        acc[x] = acc[up] ^ worth[x]
        home[x], result[x] = forest.branch(home[up], acc[x])

    return result


def main():
    tokens = iter(sys.stdin.buffer.read().split())
    cases = int(next(tokens))
    lines = []
    for _ in range(cases):
        n = int(next(tokens))
        link = [int(next(tokens)) - 1 for _ in range(n)]
        worth = [int(next(tokens)) for _ in range(n)]
        lines.append(" ".join(map(str, solve_case(n, link, worth))))
    sys.stdout.write("\n".join(lines) + "\n")


main()