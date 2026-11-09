t = int(input())

for _ in range(t):
    n, r = map(int, input().split())
    requests = list(map(int, input().split()))

    road = [0, 0]
    cnt = 0

    for i in requests:
        road.sort()

        if road[0] > i:
            break

        road[0] = max(i, road[1]) + r
        cnt += 1

    if cnt == n:
        print("YES")
    else:
        print("NO")