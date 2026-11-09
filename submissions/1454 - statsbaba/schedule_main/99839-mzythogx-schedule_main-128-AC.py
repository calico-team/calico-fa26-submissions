import sys
import heapq

def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    
    it = iter(data)
    test_cases = int(next(it))
    output = []
    sys.setrecursionlimit(10000)
    
    for _ in range(test_cases):
        num_courses = int(next(it))
        num_semesters = int(next(it))
        max_per_sem = int(next(it))
        
        prereq = [0] * (num_courses + 1)
        children = [[] for _ in range(num_courses + 1)]
        roots = []
        
        for course in range(1, num_courses + 1):
            p = int(next(it))
            prereq[course] = p
            if p == 0:
                roots.append(course)
            else:
                children[p].append(course)
        
        # Compute the height of each course (longest path to a leaf)
        height = [0] * (num_courses + 1)
        
        def compute_height(node):
            if not children[node]:
                height[node] = 0
                return 0
            tallest = 0
            for child in children[node]:
                h = compute_height(child)
                if h > tallest:
                    tallest = h
            height[node] = tallest + 1
            return height[node]
        
        for root in roots:
            compute_height(root)
        
        # Max-heap of available courses, keyed by height.
        # Python's heapq is a min-heap, so we store negative heights.
        available = []
        for root in roots:
            heapq.heappush(available, (-height[root], root))
        
        taken = 0
        
        for semester in range(num_semesters):
            if not available:
                break
            
            next_semester = []
            
            for _ in range(max_per_sem):
                if not available:
                    break
                neg_h, course = heapq.heappop(available)
                taken += 1
                for child in children[course]:
                    next_semester.append(child)
            
            for child in next_semester:
                heapq.heappush(available, (-height[child], child))
        
        output.append(str(taken))
    
    sys.stdout.write("\n".join(output))

if __name__ == "__main__":
    solve()