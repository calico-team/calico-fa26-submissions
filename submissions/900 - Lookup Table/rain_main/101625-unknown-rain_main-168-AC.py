t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    north = {}
    east = {}
    for _ in range(n):
        x, y, z, d = input().split()
        x, y, z = int(x), int(y), int(z)
        goon = x + y
        if d == "N":
            skib = north[goon] = north.get(goon, [])
            skib.append((x, y))
        if d == "E":
            skib = east[goon] = east.get(goon, [])
            skib.append(x)
    for key, item in east.items():
        east[key] = sorted(item)
    ans = n * k
    for key, a in north.items():
        current = east.get(key, None)
        if current is None:
            continue
        for x1, y1 in a:
            lo, hi = 0, len(current)
            while lo < hi:
                mid = (lo + hi) // 2
                if current[mid] < x1 + 1:
                    lo = mid + 1
                else:
                    hi = mid
            right = lo
            lo, hi = 0, len(current)
            while lo < hi:
                mid = (lo + hi) // 2
                if current[mid] < x1 - k + 1:
                    lo = mid + 1
                else:
                    hi = mid
            left = lo
            ans -= right - left
    print(ans)