t = int(input())
for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    charge = 2
    next_charge = 0
    for j in range(n):
        current_time = a[j]

        while charge < 2 and current_time >= next_charge:
            charge += 1
            next_charge += r

        if charge == 0:
            print("NO")
            break

        if charge == 2:
            next_charge = current_time + r

        if charge != 0:
            charge -= 1


    else:
        print("YES")