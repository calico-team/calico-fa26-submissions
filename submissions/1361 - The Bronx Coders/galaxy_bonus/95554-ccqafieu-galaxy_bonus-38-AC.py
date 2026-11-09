import sys

class GridConnectivity:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find_leader(self, node):
        path = []
        while self.parent[node] != node:
            path.append(node)
            node = self.parent[node]
        for item in path:
            self.parent[item] = node
        return node

    def connect(self, u, v):
        root_u = self.find_leader(u)
        root_v = self.find_leader(v)
        if root_u != root_v:
            if self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            elif self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1

def can_step(tile_a, tile_b):
    return tile_a + tile_b not in ("BR", "RB")

def run_program():
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    
    pos = 0
    total_tests = int(tokens[pos])
    pos += 1
    results = []
    
    for _ in range(total_tests):
        height = int(tokens[pos])
        width = int(tokens[pos + 1])
        num_q = int(tokens[pos + 2])
        pos += 3
        
        board = tokens[pos : pos + height]
        pos += height
        
        dsu = GridConnectivity(height * width)
        
        for y in range(height):
            row_str = board[y]
            base_idx = y * width
            for x in range(width):
                cell_idx = base_idx + x
                ch = row_str[x]
                if x + 1 < width and can_step(ch, row_str[x + 1]):
                    dsu.connect(cell_idx, cell_idx + 1)
                if y + 1 < height and can_step(ch, board[y + 1][x]):
                    dsu.connect(cell_idx, cell_idx + width)
                    
        for _ in range(num_q):
            sy = int(tokens[pos])
            sx = int(tokens[pos + 1])
            ey = int(tokens[pos + 2])
            ex = int(tokens[pos + 3])
            pos += 4
            
            start_node = sy * width + sx
            end_node = ey * width + ex
            
            if dsu.find_leader(start_node) == dsu.find_leader(end_node):
                results.append("YES")
            else:
                results.append("NO")
                
    print("\n".join(results))

if __name__ == "__main__":
    run_program()