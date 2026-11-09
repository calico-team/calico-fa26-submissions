import heapq
T = int(input())
for _ in range(T):
    N, R = map(int, input().split())
    requests = list(map(int, input().split()))
    smokes = [0, 0]
    for req in requests:
        top = heapq.heappop(smokes)
        if top <= req:
            othertop = heapq.heappop(smokes)
            if req >= othertop:
                heapq.heappush(smokes, req + R)
            else:
                heapq.heappush(smokes, othertop + R)
            heapq.heappush(smokes, othertop)
        else:
            print("NO")
            break
    else:
        print("YES")
