import heapq


def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    child=[[] for _ in range(N)]
    r=[]
    for i,p in enumerate(P):
        if p==0:
            r.append(i)
        else:
            
            child[p-1].append(i)
    order=[]
    stack=r[:]
    while stack:
        node=stack.pop()
        order.append(node)
        stack.extend(child[node])
        
    h=[1]*N
    for node in reversed(order):
        for c in child[node]:
            h[node]=max(h[node],h[c]+1)
    
    available=[(-h[node],node) for node in r]
    heapq.heapify(available)
    complete=0
    for _ in range(min(M, N)):
       if not available:
              break
      
       this_semester=[]
       for _ in range(min(K, len(available))):
             
              _,node=heapq.heappop(available)
              this_semester.append(node)
       complete+=len(this_semester)
       
       for node in this_semester:
                for c in child[node]:
                        
                    heapq.heappush(available,(-h[c],c))
    return complete


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()