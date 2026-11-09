import sys

# Increase recursion depth just in case
sys.setrecursionlimit(300000)

def main():
    dinosauraus = sys.stdin.read().split()
    if not dinosauraus:
        return
    
    iterator = iter(dinosauraus)
    T = int(next(iterator))
    
    out = []
    
    for _ in range(T):
        N = int(next(iterator))
        
        # Convert to 0-based indexing for words (1 to N -> 0 to N-1)
        A = [int(next(iterator)) - 1 for _ in range(N)]
        V = [int(next(iterator)) for _ in range(N)]
        
        # rev store links pointing back to node i
        rev = [[] for _ in range(N)]
        indeg = [0] * N
        
        for i in range(N):
            rev[A[i]].append(i)
            indeg[A[i]] += 1
            
        # Kahn's algorithm / Topological sort to remove trees and isolate cycles
        q = [i for i in range(N) if indeg[i] == 0]
        head = 0
        while head < len(q):
            u = q[head]
            head += 1
            v = A[u]
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
                
        ans = [0] * N
        visited = [False] * N
        
        # Process each functional graph component / cycle
        for i in range(N):
            if indeg[i] == 0 or visited[i]:
                continue
                
            # Find all nodes in this cycle
            cycle = []
            curr = i
            while True:
                cycle.append(curr)
                visited[curr] = True
                curr = A[curr]
                if curr == i:
                    break
            
            # XOR sum of the full cycle
            cycle_total_xor = 0
            for node in cycle:
                cycle_total_xor ^= V[node]
                
            # For each starting point in the cycle
            for start in cycle:
                prefix_xors = []
                current_xor = 0
                curr = start
                
                # Get prefix XORs along the cycle
                for _ in range(len(cycle)):
                    current_xor ^= V[curr]
                    prefix_xors.append(current_xor)
                    curr = A[curr]
                    
                # If cycle total is non-zero, going 2 laps gives more reachable XOR values
                if cycle_total_xor != 0:
                    prefix_xors += [val ^ cycle_total_xor for val in prefix_xors]
                    
                ans[start] = max(prefix_xors)
                
                # Dynamic Binary Trie array allocation
                ch0 = [-1]
                ch1 = [-1]
                
                def insert_trie(num):
                    node = 0
                    for b in range(29, -1, -1):
                        bit = (num >> b) & 1
                        if bit == 0:
                            if ch0[node] == -1:
                                ch0[node] = len(ch0)
                                ch0.append(-1)
                                ch1.append(-1)
                            node = ch0[node]
                        else:
                            if ch1[node] == -1:
                                ch1[node] = len(ch0)
                                ch0.append(-1)
                                ch1.append(-1)
                            node = ch1[node]
                            
                def query_trie(num):
                    node = 0
                    res = 0
                    for b in range(29, -1, -1):
                        bit = (num >> b) & 1
                        if bit == 0:
                            nxt = ch1[node]
                            if nxt != -1:
                                res |= (1 << b)
                                node = nxt
                            else:
                                node = ch0[node]
                        else:
                            nxt = ch0[node]
                            if nxt != -1:
                                res |= (1 << b)
                                node = nxt
                            else:
                                node = ch1[node]
                    return res

                # Insert all valid paths from the cycle starting point
                for val in prefix_xors:
                    insert_trie(val)
                insert_trie(0)
                
                # DFS down into incoming tree branches attached to the cycle
                stack = [(start, 0)]
                while stack:
                    u, path_xor = stack.pop()
                    path_xor ^= V[u]
                    
                    ans[u] = max(ans[u], query_trie(path_xor))
                    insert_trie(path_xor)
                    
                    for child in rev[u]:
                        if indeg[child] == 0:
                            stack.append((child, path_xor))
                            
        out.append(" ".join(map(str, ans)))
        
    print("\n".join(out))

def read_your_input():
    return sys.stdin.readline

if __name__ == "__main__":
    main()