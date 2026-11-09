import sys
import heapq
inp = [line.strip() for line in sys.stdin]

for itr in range(1, len(inp), 2):
    n, m, k = map(int, inp[itr].split()) # n courses, m sem, max k per sem
    p = list(map(int, inp[itr+1].split())) # n course 1 to n, prereq p_i (p[i-1])

    npost = [0] * n
    for i in range(1, n+1): # do dfs
        course = i
        chain = 0 # num of courses needed before
        while p[course-1] != 0:
            chain += 1
            course = p[course-1]
            npost[course-1] = max(npost[course-1], chain)

    pq = []
    for i in range(n):
        heapq.heappush(pq, (-npost[i], i+1))
    # print(npost)

    seen = set()
    ans = 0
    # if there were a prereq to the longest chain, that would be longest chain +1
    for _ in range(m): # m sem, k per m
        if not pq:
            break
        kk = 0
        nextseen = seen.copy()
        skipped = []
        while pq and kk < k: 
            longest = heapq.heappop(pq)
            if (p[longest[1]-1] == 0 or p[longest[1]-1] in seen):
                kk += 1
                nextseen.add(longest[1])
            else:
                skipped.append(longest) # need to skip some to add the shorter postreq but valid to fill k
        for x in skipped:
            heapq.heappush(pq, x)
        ans += kk
        seen = nextseen.copy()
    
    print(ans)


