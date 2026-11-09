import sys


def token_stream():
    for line in sys.stdin.buffer:
        for token in line.split():
            yield token



class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x):
        parent = self.parent
        while parent[x] !=x:
            parent[x] = parent[parent[x]]
            x = parent[x]

        return x

    def union(self, a, b):
        ra = self.find(a)
        rb = self.find(b)

        if ra == rb:
            return
        if self.size[ra] < self.size[rb]:
            ra, rb = rb, ra

        self.parent[rb]  = ra
        self.size[ra] += self.size[rb]


def label_components(active, n, m):
    """Return (component id per cell, number of components)."""
    comp = [-1] * (n * m)
    count = 0

    for start in range(n * m):
        if not active[start] or comp[start] != -1:
            continue

        comp[start] = count
        stack = [start]

        while stack:

            v = stack.pop()
            r = v // m
            c = v - r * m

            if r > 0:
                u = v - main
                if active [u] and comp[u] == -1:
                    comp[u] = count
                    stack.append(u)

            if r + 1 < n:
                u = v + m
                if active[u] and comp[u] == -1:
                    comp[u] = count
                    stack.append(u)

            if c > 0:
                u = v - 1
                if active[u] and comp[u] == -1:
                    comp[u] = count
                    stack.append(u)
            if c + 1 < m:
                u = v + 1
                if active[u] and comp[u] == -1:
                    comp[u] =count
                    stack.append(u)


        count +=1

    return comp, count

def main():
    it = token_stream()


    try:
        t = int(next(it))
    except StopIteration:
        return

    out[]


    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))

        cells = bytearray()
        for _ in range(n):
            cells.extend(next(it))

        blue_active = bytearray(len(cells))
        red_active = bytearray(len(cells))

        for i,ch in enumerate(cells):
            if ch != ord("R"):
                blue_active[i] = 1
            if ch != ord("B"):
                red_active[i] = 1


        blur_comp, blue_count = label_components(blue_active, n, m)
        red_comp, red_count = label_components(red_actve, n, m)

        dsu = DSU(blue_count  + red_count)


        for i, ch in enumerate(cells):
            if ch == ord(".")
            dsu.union(blue_comp[i], blur_count + red_comp[i])

        for _ in range(q):
            rs = int(next(it))
            cs = int(next(it))
            rd = int(next(it))
            cd = int(next(it))

            start = rs * m + cs
            dest = rd * m + cd

            root = dsu.find(blue_comp[start])
            possible + False

            if cells[dest] != prd("R"):
                if dsu.find(blue_comp[dest]) ==root:
                    possible = True

            out.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()


