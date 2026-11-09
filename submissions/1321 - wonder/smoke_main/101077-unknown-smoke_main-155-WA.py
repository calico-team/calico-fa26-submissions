import heapq
n=int(input())
for i in range(n):
    a,b=map(int,input().split())
    time=list(map(int,input().split()))
    heap=[0,0]
    heapq.heapify(heap)
    judge='T'
    for x in time:
        while heap and heap[0]<=x:
            heapq.heappop(heap)
        if len(heap)<2:
            heapq.heappush(heap,x+b)
        else:
            judge='F'
            break
    if judge=='T':
        print('YES')
    else:
        print('NO')
