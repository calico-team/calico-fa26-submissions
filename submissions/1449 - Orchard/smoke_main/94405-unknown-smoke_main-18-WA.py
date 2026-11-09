

lines = int(input())

for i in range(lines):
    line = input()
    items = line.split()
    charge_rate = int(items[1])
    prev_time = 0
    prev_charge = 0

    can_charge = True
    for time in input().split():
        time = int(time)
        prev_charge = min(prev_charge + time - prev_time, 2 * charge_rate)
        if prev_charge < charge_rate:
            print("NO")
            can_charge = False
            break
        else:
            prev_charge -= charge_rate
        prev_time = time

    if can_charge:
        print("YES")

