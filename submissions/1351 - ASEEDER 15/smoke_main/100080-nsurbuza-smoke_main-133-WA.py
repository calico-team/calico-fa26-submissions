t = int(input())
for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    next_first_charge, next_second_charge = 0, 0
    for j in range(n):
        current_time = a[j]

        # Initial charging
        if next_first_charge == 0:
            next_first_charge = current_time + r
        elif next_second_charge == 0 and next_first_charge != 0:
            next_second_charge = next_first_charge + r

        if current_time >= next_first_charge:
            next_first_charge = next_second_charge + r
        elif current_time >= next_second_charge:
            next_second_charge = next_first_charge + r
        else:
            print("NO")
            break
    else:
        print("YES")