t = int(input())

for j in range(t):
    n, k = map(int, input().split())
    groups = {}

    for i in range(n):
        x, y, z, d = input().split()
        x, y, z = int(x), int(y), int(z)
        s = x + y
        if s not in groups:
            groups[s] = [[], []]
        if d == 'N':
            groups[s][0].append((x, z))
        else:
            groups[s][1].append((x, z))

    blocked = 0

    for s in groups:
        n_drone, e_drone = groups[s]
        n_drone.sort()
        sorted_x = [x for x, z in n_drone]
        for x, z in e_drone:
            l = 0
            r = len(sorted_x)
            while l < r:
                mid = (l + r) // 2
                if sorted_x[mid] < x:
                    l = mid + 1
                else:
                    r = mid
            left = l
            l = 0
            r = len(sorted_x)

            while l < r:
                mid = (l + r) // 2
                if sorted_x[mid] <= x + k - 1:
                    l = mid + 1
                else:
                    r = mid
            right = l
            total = right - left
            blocked += total
    print(n * k - blocked)
