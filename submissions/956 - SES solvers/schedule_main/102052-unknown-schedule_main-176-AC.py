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
    chld=[[] for i in range(N+1)]
    rts=[]
    for i in range(1,N+1):
       if P[i-1]==0:
         rts.append(i)
       else:
         e=P[i-1]
         chld[e].append(i)
    odr=rts[:]
    for v in odr:
              for c in chld[v]:
                  odr.append(c)
    hght=[1]*(N+1)
    for v in reversed(odr):
         e=P[v-1]
         if e!=0:
            h=hght[v]+1
            if hght[e]<h:
               hght[e]=h
    heap=[]
    for r in rts:
         heap.append((-hght[r],r))
    heapq.heapify(heap)
    all=0
    for i in range(M):
              if len(heap)==0:
                    break
              taken=[]
              count=min(K,len(heap))
              for j in range(count):
                  item=heapq.heappop(heap)
                  taken.append(item[1])
              all=all+len(taken)
              for v in taken:
                 for c in chld[v]:
                      item=(-hght[c],c)
                      heapq.heappush(heap,item)
    return all
def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()