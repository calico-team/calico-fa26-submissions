import heapq
n=int(input())
for i in range(n):
    a,b=map(int,input().split())
    time=list(map(int,input().split()))
    heap=[0,0]
    heapq.heapify(heap)
    judge='T'
    end=0
    for x in time:
        if heap[0]<=x:
            heapq.heappop(heap)
            start=max(x,end)
            new=start+b
            heapq.heappush(heap,new)
            end=new
        else:
            judge='F'
            break
    if judge=='T':
        print('YES')
    else:
        print('NO')
