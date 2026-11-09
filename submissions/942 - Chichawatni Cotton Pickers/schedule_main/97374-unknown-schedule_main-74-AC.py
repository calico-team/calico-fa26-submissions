import sys
from collections import deque

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    """
    adj = [[] for _ in range(N + 1)]
    in_degree = [0] * (N + 1)
    
    for i in range(1, N + 1):
        prereq = P[i - 1]
        if prereq != 0:
            adj[prereq].append(i)
            in_degree[i] += 1
            
    # Group courses by their topological generation/depth from roots
    # Find all root nodes (in_degree == 0)
    queue = deque()
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            queue.append(i)
            
    # To handle semester capacities correctly, we can sort or prioritize nodes by their subtree height / depth
    # or use a min-heap where we group by available generations.
    # Actually, a standard approach for course schedule with capacity K per semester:
    # We can simulate semester by semester by pushing currently available courses into a priority queue 
    # and taking up to K of them. But to avoid premature bottlenecking, we should prioritize nodes 
    # that have more dependent descendants (longest path to leaves).
    
    # Compute height (longest path from node to any descendant leaf) for priority ordering
    height = [0] * (N + 1)
    
    # We can compute heights by working backwards from leaves
    # First, find out-degrees and leaf nodes
    out_degree = [len(adj[i]) for i in range(N + 1)]
    leaf_queue = deque([i for i in range(1, N + 1) if out_degree[i] == 0 and in_degree[i] >= 0])
    
    # Alternatively, compute depths via memoized DFS or simple topological traversal backwards
    visited_in_deg = in_degree.copy()
    
    import heapq
    # Max-heap equivalent using negative height so larger height (most critical path) comes first
    # If heights are equal, smaller course ID comes first
    avail = []
    for i in range(1, N + 1):
        if visited_in_deg[i] == 0:
            # We can use a heuristic: height or simply a min-heap. Let's compute exact node depths.
            pass
            
    # Let's compute depth/height for each node:
    def get_height(u):
        if height[u] != 0:
            return height[u]
        h = 1
        for v in adj[u]:
            h = max(h, 1 + get_height(v))
        height[u] = h
        return h

    for i in range(1, N + 1):
        if height[i] == 0:
            get_height(i)
            
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            # Push (-height[i], i) into heap so nodes with greater remaining dependencies are prioritized
            heapq.heappush(avail, (-height[i], i))
            
    total_courses = 0
    
    for _ in range(M):
        if not avail:
            break
            
        today_courses = []
        # Take up to K courses this semester
        count = min(K, len(avail))
        for _ in range(count):
            h, u = heapq.heappop(avail)
            today_courses.append(u)
            total_courses += 1
            
        for u in today_courses:
            for v in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    heapq.heappush(avail, (-height[v], v))
                    
    return total_courses

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        K = int(input_data[idx+2])
        idx += 3
        
        P = []
        for _ in range(N):
            P.append(int(input_data[idx]))
            idx += 1
            
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()
