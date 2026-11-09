for _ in range(int(input())):
    n, r = map(int,input().split())
    a = list(map(int,input().split()))
    if all(a[i+2] - a[i] >= r for i in range(n-2)) and all(a[i+3] - a[i] >= 2 * r for i in range(n-3)):
        print("YES")
    else:
        print("NO")
