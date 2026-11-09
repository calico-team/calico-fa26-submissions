import sys

sys.setrecursionlimit(300000)

def main():
    stream = sys.stdin.read().split()
    if not stream:
        return
    
    tokens = iter(stream)
    num_cases = int(next(tokens))
    
    for _ in range(num_cases):
        n = int(next(tokens))
        m = int(next(tokens))
        k = int(next(tokens))
        
        parents = [0] * (n + 1)
        graph = [[] for _ in range(n + 1)]
        in_degree = [0] * (n + 1)
        
        for i in range(1, n + 1):
            p = int(next(tokens))
            parents[i] = p
            if p != 0:
                graph[p].append(i)
                in_degree[i] += 1
                
        tree_heights = [0] * (n + 1)
        
        def calculate_height(node):
            if tree_heights[node] != 0:
                return tree_heights[node]
            
            max_child_height = 0
            for child in graph[node]:
                max_child_height = max(max_child_height, calculate_height(child))
                
            tree_heights[node] = 1 + max_child_height
            return tree_heights[node]

        for i in range(1, n + 1):
            if in_degree[i] == 0:
                calculate_height(i)
                
        available = []
        for i in range(1, n + 1):
            if in_degree[i] == 0:
                available.append(i)
                
        courses_completed = 0
        
        for semester in range(m):
            if not available:
                break
                
            available.sort(key=lambda x: tree_heights[x], reverse=True)
            
            take_count = min(k, len(available))
            current_semester_courses = available[:take_count]
            available = available[take_count:]
            
            courses_completed += take_count
            newly_eligible = []
            
            for course in current_semester_courses:
                for child in graph[course]:
                    in_degree[child] -= 1
                    if in_degree[child] == 0:
                        newly_eligible.append(child)
                        
            available.extend(newly_eligible)
            
        print(courses_completed)

if __name__ == '__main__':
    main()
