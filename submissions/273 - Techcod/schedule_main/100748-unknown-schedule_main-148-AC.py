import heapq
import sys
def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator=iter(input_data)
    num_test_case= int(next(iterator))
    output=[]
    for _ in range(num_test_case):
        n =int(next(iterator))
        m =int(next(iterator))
        k=int(next(iterator))
        p =[int(next(iterator)) for _ in range(n)]        
        children= [[] for _ in range(n)]
        roots =[]
        
        for i in range(n):
            parent=p[i]
            if parent==0:
                roots.append(i)
            else:
                children[parent-1].append(i)        
        order=[]
        stack=list(roots)
        while stack:
            curr =stack.pop()
            order.append(curr)
            for child in children[curr]:
                stack.append(child)        
        height =[1]*n
        for curr in reversed(order):
            for child in children[curr]:
                height[curr]=max(height[curr], height[child]+1)        
        
        pq =[]
        for root in roots:
            heapq.heappush(pq, (-height[root], root))        
        total_process=0
        for _ in range(m):
            batch =[]
            for _ in range(k):
                if not pq:
                    break
                _, curr =heapq.heappop(pq)
                batch.append(curr)
                total_process+=1
            
            for curr in batch:
                for child in children[curr]:
                    heapq.heappush(pq, (-height[child], child))            
            if not pq:
                break        
        output.append(str(total_process))        
    print('\n'.join(output))

if __name__ =="__main__":
    main()