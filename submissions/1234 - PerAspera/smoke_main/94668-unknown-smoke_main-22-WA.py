t = int(input())

for _ in range(t):
    n, r = map(int, input().split())

    req = list(map(int, input().split()))
    yes = True
    for i in range(n):
        if i == 0:
            continue

        if len(req) > 1:
            if req[i] - req[i - 1] < r:
                yes = False
                break
        else:
            break

    if yes:
        print("YES")
    else:
        print("NO")
