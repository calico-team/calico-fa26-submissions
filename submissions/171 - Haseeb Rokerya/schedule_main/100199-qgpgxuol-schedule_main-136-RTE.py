# cook your dish here
import sys
import heapq

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        T_str = next(iterator, None)
        if T_str is None:
            return
        T = int(T_str)
    except (StopIteration, ValueError):
        return
    
    out = []
    for _ in range(T):
        try:
            n_str = next(iterator, None)
            m_str = next(iterator, None)
            k_str = next(iterator, None)
            if n_str is None or m_str is None or k_str is None:
                break
            n = int(n_str)
            m = int(m_str)
            k = int(k_str)
        except (StopIteration, ValueError):
            break
        
        # Dynamically size lists up to max possible index to prevent out-of-bounds errors
        max_idx = max(n + 1, 2)
        children = [[] for _ in range(max_idx)]
        roots = []
        
        for i in range(1, n + 1):
            try:
                p_str = next(iterator, "0")
                p = int(p_str)
            except (StopIteration, ValueError):
                p = 0
            
            # Ensure p is within valid bounds [1, n], otherwise treat as root (0)
            if p <= 0 or p > n or p == i:
                roots.append(i)
            else:
                # Dynamically expand children list if p exceeds current bounds (Fixed syntax error here)
                if p >= len(children):
                    children.extend([[] for _ in range(p - len(children) + 1)])
                children[p].append(i)
                
        # BFS order to get nodes, then process in reverse for bottom-up heights
        order = list(roots)
        idx_order = 0
        while idx_order < len(order):
            v = order[idx_order]
            idx_order += 1
            if v < len(children):
                for c in children[v]:
                    order.append(c)
            
        height = [1] * max(n + 1, len(children))
        for v in reversed(order):
            h = 1
            if v < len(children):
                for c in children[v]:
                    if c < len(height) and height[c] + 1 > h:
                        h = height[c] + 1
            if v < len(height):
                height[v] = h
            
        heap = []
        for r in roots:
            h_val = height[r] if r < len(height) else 1
            heap.append((-h_val, r))
        heapq.heapify(heap)
        
        total = 0
        for _ in range(m):
            if not heap:
                break
            taken = []
            while heap and len(taken) < k:
                taken.append(heapq.heappop(heap)[1])
            total += len(taken)
            for v in taken:
                if v < len(children):
                    for c in children[v]:
                        h_val = height[c] if c < len(height) else 1
                        heapq.heappush(heap, (-h_val, c))
                    
        out.append(str(total))
        
    print("\n".join(out))

if __name__ == '__main__':
    main()