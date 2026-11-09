import sys
import heapq
inp = [line.strip() for line in sys.stdin]
T = int(inp[0])

for i in range(1, len(inp), 2):
    n, r = map(int, inp[i].split()) # num smoke req, seconds for recharge
    a = list(map(int, inp[i+1].split())) # time each req
    # print(n, r, a)

    smokes = [2, 0]
    heapq.heapify(a)
    ans = "YES"
    while a:
        req = heapq.heappop(a)
        if smokes[1] + r <= req:
            smokes[0] = min(2, smokes[0]+1)
        if smokes[0] > 0:
            smokes[0] -= 1
            smokes[1] = req
        else:
            ans = "NO"
    print(ans)
