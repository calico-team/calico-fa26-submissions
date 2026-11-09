
class DisjointSet:
    def __init__(self, count):
        self.parent = list(range(count))
        self.weight = [1] * count

    def find_root(self, node):
        if node != self.parent[node]:
            self.parent[node] = self.find_root(self.parent[node])
        return self.parent[node]

    def merge(self, first, second):
        root1 = self.find_root(first)
        root2 = self.find_root(second)

        if root1 == root2:
            return

        if self.weight[root1] < self.weight[root2]:
            root1, root2 = root2, root1

        self.parent[root2] = root1
        self.weight[root1] += self.weight[root2]


def solve():
    test_cases = int(input())

    for _ in range(test_cases):
        rows, cols, queries = map(int, input().split())

        board = []
        for _ in range(rows):
            board.append(input().strip())

        cells = rows * cols
        groups = DisjointSet(2 * cells)

        def cell_id(row, col, color):
            return color * cells + row * cols + col

        def is_allowed(value, color):
            if value == '.':
                return True
            if color == 0 and value == 'B':
                return True
            if color == 1 and value == 'R':
                return True
            return False

        moves = [(0, 1), (1, 0)]

        for row in range(rows):
            for col in range(cols):

                for color in range(2):
                    if not is_allowed(board[row][col], color):
                        continue

                    current = cell_id(row, col, color)

                    for row_change, col_change in moves:
                        next_row = row + row_change
                        next_col = col + col_change

                        if 0 <= next_row < rows and 0 <= next_col < cols:
                            if is_allowed(board[next_row][next_col], color):
                                adjacent = cell_id(next_row, next_col, color)
                                groups.merge(current, adjacent)

                if board[row][col] == '.':
                    blue_node = cell_id(row, col, 0)
                    red_node = cell_id(row, col, 1)
                    groups.merge(blue_node, red_node)

        for _ in range(queries):
            start_row, start_col, end_row, end_col = map(int, input().split())

            start = cell_id(start_row, start_col, 0)
            reachable = False

            for color in range(2):
                if is_allowed(board[end_row][end_col], color):
                    finish = cell_id(end_row, end_col, color)

                    if groups.find_root(start) == groups.find_root(finish):
                        reachable = True
                        break

            print("YES" if reachable else "NO")


solve()
