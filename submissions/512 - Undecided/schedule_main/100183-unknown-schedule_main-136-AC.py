import heapq

t = int(input())
for _ in range(t):
    n,m,k = map(int,input().split())
    adj = [[] for _ in range(n)]
    p = [int(i)-1 for i in input().split()] # Input array and subtract 1 to every value
    # For every course, find the number of courses it unlocks
    for course,pv in enumerate(p):
        if pv!=-1:
            adj[pv].append(course)
    size = [0]*n
    def treesize(node):
        if size[node]:
            return size[node]
        else:
            size[node]=1
        for next in adj[node]:
            treesize(next)
            size[node]+=size[next]
    queue = []
    for course,pv in enumerate(p):
        treesize(course)
        if pv==-1: # Begin
            heapq.heappush(queue,(-size[course],course))
    # print("TS",size)
    crs=0
    for i in range(m):
        unlock = [] # These courses can only be selected in the next semester
        # print(queue)
        for j in range(k):
            # Take top K courses in priority queue
            if not queue:
                break
            csize,course = heapq.heappop(queue)
            crs+=1
            csize=-csize
            for nxt in adj[course]:
                unlock.append((-size[nxt],nxt))
        # Put the unlocked courses in the queue
        for x in unlock:
            heapq.heappush(queue,x)
    print(crs)