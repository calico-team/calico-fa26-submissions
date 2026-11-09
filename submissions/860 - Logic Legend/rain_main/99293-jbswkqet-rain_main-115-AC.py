# Source: https://usaco.guide/general/io
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right


class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)

    def add(self, i, value):
        i += 1  
        while i <= self.n:
            self.bit[i] += value
            i += i & -i

    def prefix_sum(self, end):
        """Sum of elements at indices [0, end)."""
        result = 0
        while end > 0:
            result += self.bit[end]
            end -= end & -end
        return result

    def range_sum(self, left, right):
        """Sum of elements at indices [left, right)."""
        return self.prefix_sum(right) - self.prefix_sum(left)


def solve():
    data = sys.stdin.buffer.read().split()
    it = iter(data)

    T = int(next(it))
    answers = []

    for _ in range(T):
        n = int(next(it))
        k = int(next(it))

        groups = defaultdict(list)

        for _ in range(n):
            x = int(next(it))
            y = int(next(it))
            z = int(next(it))
            direction = next(it).decode()
            groups[x + y].append((x, z, direction))

        blocked = 0

        for drones in groups.values():
            xs = sorted(x for x, _, _ in drones)
            east_tree = Fenwick(len(xs))
            north_tree = Fenwick(len(xs))

            
            drones.sort(key=lambda drone: -drone[1])

            i = 0
            while i < len(drones):
                j = i
                height = drones[i][1]

                while j < len(drones) and drones[j][1] == height:
                    j += 1

                
                for x, _, direction in drones[i:j]:
                    if direction == 'E':
                    
                        left_x = x
                        right_x = x + k - 1

                        left = bisect_left(xs, left_x)
                        right = bisect_right(xs, right_x)
                        blocked += north_tree.range_sum(left, right)
                    else:
                        
                        left_x = x - k + 1
                        right_x = x

                        left = bisect_left(xs, left_x)
                        right = bisect_right(xs, right_x)
                        blocked += east_tree.range_sum(left, right)

                
                for x, _, direction in drones[i:j]:
                    idx = bisect_left(xs, x)
                    if direction == 'E':
                        east_tree.add(idx, 1)
                    else:
                        north_tree.add(idx, 1)

                i = j

        answers.append(str(n * k - blocked))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()

