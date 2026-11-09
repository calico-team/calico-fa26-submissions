import sys

# Increase recursion depth for deep tree structures
sys.setrecursionlimit(300000)

class XORBasis:
    """Maintains a bitwise XOR linear basis for fast maximum XOR queries."""
    def _init_(self):
        self.basis = []

    def insert(self, mask: int):
        for b in self.basis:
            mask = min(mask, mask ^ b)
        if mask > 0:
            self.basis.append(mask)
            self.basis.sort(reverse=True)

    def get_max(self, val: int) -> int:
        for b in self.basis:
            val = max(val, val ^ b)
        return val


def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))
    
    out = []

    for _ in range(T):
        N = int(next(iterator))
        
        # 1-based indexing for convenience
        W = [0] + [int(next(iterator)) for _ in range(N)]
        V = [0] + [int(next(iterator)) for _ in range(N)]

        # State tracking for cycle detection:
        # 0: unvisited, 1: visiting (in current stack), 2: visited
        state = [0] * (N + 1)
        comp_id = [0] * (N + 1)
        bases = []
        
        # 1. Identify cycles and build XOR basis per component
        for i in range(1, N + 1):
            if state[i] != 0:
                continue
            
            curr = i
            path = []
            while curr != 0 and state[curr] == 0:
                state[curr] = 1
                path.append(curr)
                curr = W[curr]

            if curr != 0 and state[curr] == 1:
                # Cycle found!
                cid = len(bases)
                basis = XORBasis()
                
                # Find start index of cycle in the current path
                cycle_start_idx = path.index(curr)
                cycle_nodes = path[cycle_start_idx:]
                
                # Compute cycle total XOR sum
                cycle_xor = 0
                for u in cycle_nodes:
                    cycle_xor ^= V[u]
                
                basis.insert(cycle_xor)
                bases.append(basis)

                for u in path:
                    comp_id[u] = cid
                    state[u] = 2
            else:
                # Connected to an already processed node component
                cid = comp_id[curr]
                for u in path:
                    comp_id[u] = cid
                    state[u] = 2

        # 2. Compute maximum achievable happiness for each node
        # Using memoization on functional graph
        ans = [0] * (N + 1)
        memo = {}

        def get_ans(u):
            if u in memo:
                return memo[u]

            # Detect cycle node vs tree node
            # Dynamic computation of path to cycle + basis optimization
            visited_nodes = []
            curr = u
            curr_xor = 0
            
            while curr not in memo:
                visited_nodes.append(curr)
                curr_xor ^= V[curr]
                curr = W[curr]
                # If we loop back to start node u
                if curr == u:
                    break

            base_val = memo[curr] if curr in memo else 0
            
            # Unwind path and store max XOR using component basis
            curr_val = 0
            cid = comp_id[u]
            
            # Standard path propagation
            for node in reversed(visited_nodes):
                curr_val ^= V[node]
                res = bases[cid].get_max(curr_val)
                memo[node] = res
                
            return memo[u]

        # Process all nodes
        for i in range(1, N + 1):
            if i not in memo:
                # Calculate simple cycle path max or tree path max
                get_ans(i)

        out.append(" ".join(str(memo[i]) for i in range(1, N + 1)))

    print("\n".join(out))


if _name_ == "_main_":
    solve()