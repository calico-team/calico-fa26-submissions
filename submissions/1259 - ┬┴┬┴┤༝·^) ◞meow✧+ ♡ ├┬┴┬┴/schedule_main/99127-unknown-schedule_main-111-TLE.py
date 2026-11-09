import sys
import heapq
inp = [line.strip() for line in sys.stdin]

for itr in range(1, len(inp), 2):
    n, m, k = map(int, inp[itr].split()) # n courses, m sem, max k per sem
    p = list(map(int, inp[itr+1].split())) # n course 1 to n, prereq p_i (p[i-1])

    npost = [0] * n
    children = [[] for _ in range(n)]
    for i in range(1, n+1): # do dfs
        if p[i-1] != 0:
            children[p[i-1]-1].append(i-1)
        course = i
        chain = 0 # num of courses needed before
        while p[course-1] != 0:
            chain += 1
            course = p[course-1]
            npost[course-1] = max(npost[course-1], chain)

    pq = []
    for i in range(n):
        if p[i] == 0:
            heapq.heappush(pq, (-npost[i], i+1)) # only available to take now

    # if there were a prereq to the longest chain, that would be longest chain +1
    ans = 0
    for _ in range(m): 
        if not pq:
            break
        take = []
        while pq and len(take) < k: 
            longest = heapq.heappop(pq)
            # if (p[longest[1]-1] == 0 or p[longest[1]-1] in seen):
            take.append(longest[1])
        for course in take: # push in the next possible courses after this sem
            for ch in children[course-1]:
                heapq.heappush(pq, (-npost[ch], ch+1))
        ans += len(take)
    print(ans)

