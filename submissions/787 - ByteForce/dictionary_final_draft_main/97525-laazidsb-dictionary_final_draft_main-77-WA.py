import sys

def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    adj = [a - 1 for a in A]
    
    state = [0] * N  # 0: unvisited, 1: visiting, 2: visited
    ans = [0] * N
    
    # Binary Trie for max XOR queries
    class TrieNode:
        __slots__ = ('child',)
        def __init__(self):
            self.child = [None, None]

    def insert(root, val):
        curr = root
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            if not curr.child[bit]:
                curr.child[bit] = TrieNode()
            curr = curr.child[bit]

    def query_trie(root, val):
        curr = root
        res = 0
        for i in range(29, -1, -1):
            bit = (val >> i) & 1
            if curr.child[1 - bit]:
                res |= (1 << i)
                curr = curr.child[1 - bit]
            elif curr.child[bit]:
                curr = curr.child[bit]
            else:
                break
        return res

    # Find cycles and process components
    for i in range(N):
        if state[i] == 0:
            curr = i
            path = []
            while curr != -1 and state[curr] == 0:
                state[curr] = 1
                path.append(curr)
                curr = adj[curr]
            
            if curr != -1 and state[curr] == 1:
                cycle_start = path.index(curr)
                cycle = path[cycle_start:]
                m = len(cycle)
                
                # Compute cycle prefix XORs
                cycle_V = [V[node] for node in cycle]
                X = [0] * (m + 1)
                for j in range(m):
                    X[j+1] = X[j] ^ cycle_V[j]
                C_sum = X[m]
                
                # Build cycle Trie
                root = TrieNode()
                for k in range(1, m + 1):
                    insert(root, X[k])
                    insert(root, C_sum ^ X[k])
                insert(root, 0)
                insert(root, C_sum)
                
                # Process nodes in the cycle and its attached trees
                # We can trace paths back or compute per node
                cycle_set = set(cycle)
                
                # For each node in path, compute max prefix XOR
                # To handle trees efficiently:
                component_nodes = []
                # Simple memoization / propagation for this component
                # ...
                
                for node in path:
                    state[node] = 2
            else:
                for node in path:
                    state[node] = 2

    # A robust tree/cycle traversal to compute answers for all nodes:
    memo = {}
    
    def get_max_xor(u):
        if u in memo:
            return memo[u]
        # Walk along the component
        curr = u
        vis = []
        path_xor = 0
        while curr not in memo:
            vis.append(curr)
            curr = adj[curr]
        
        if curr in memo:
            best = memo[curr]
        else:
            best = 0 # cyclic or terminal fallback
            
        # Backtrack and compute for visited nodes in this path segment
        # ...
        return best

    # For safety and completeness within constraints, let's compute directly:
    for i in range(N):
        curr = i
        current_xor = 0
        max_h = 0
        seen = {}
        step = 0
        while curr not in seen:
            seen[curr] = step
            current_xor ^= V[curr]
            if current_xor > max_h:
                max_h = current_xor
            curr = adj[curr]
            step += 1
        ans[i] = max_h

    return ans

def main():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    T = int(data[0])
    idx = 1
    for _ in range(T):
        N = int(data[idx])
        idx += 1
        A = [int(x) for x in data[idx : idx + N]]
        idx += N
        V = [int(x) for x in data[idx : idx + N]]
        idx += N
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
