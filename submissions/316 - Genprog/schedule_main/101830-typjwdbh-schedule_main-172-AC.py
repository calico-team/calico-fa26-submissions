import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    children= [[] for _ in range (N+1)]
    roots=[]
    for i in range (1,N+1):
        p=P[i-1]
        if p==0:
            roots.append(i)
        else:
            children[p].append(i)
    order=list (roots)
    for v in order:
        order.extend(children[v])    
    height=[1]*(N+1)
    for v in reversed(order):
        for c in children[v]:
            if height[c]+1> height[v]:
                height[v]=height[c]+1
    heap=[(-height[r],r) for r in roots]  
    heapq.heapify(heap)    
    taken=0      
    for _ in range(M):
        if not heap:
            break
        batch=[]
        for _ in range(min(K, len(heap))):
            batch.append(heapq.heappop(heap)[1])
        taken+=len(batch) 
        for v in batch:
            for c in children[v]:
                heapq.heappush(heap, (-height[c], c))            
    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()