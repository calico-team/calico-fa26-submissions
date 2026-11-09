import math
data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    input_requests = input().split()
    input_requests = [int(item) for item in input_requests]
    data.append([time,input_requests])

for charge_time,requests in data:
    charges = 2
    cando = True
    last_request = 0
    prev_reload_charge = 0
    for request in requests:
        new_ = math.floor((request - prev_reload_charge)/charge_time)
        charges = min(2, charges + new_)
        charges -= 1
        prev_reload_charge += new_ * time
        if charges == 1:
            prev_reload_charge = request
        if charges < 0:
            cando = False
            break
        # print(charges, prev_reload_charge)

    if cando:
        print("YES")
    else:
        print("NO")