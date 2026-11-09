import math
data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    input_requests = input().split()
    input_requests = [int(item) for item in input_requests]
    data.append([time,input_requests])

for charge_time,requests in data:
    charges=2
    next_recharge = None
    fail = False
    for request in requests:
        while charges<2 and request>=next_recharge:
            charges+=1
            if charges<2:
                next_recharge+=charge_time
            else:
                next_recharge = None
        if charges>0:
            charges-=1
            if next_recharge == None:
                next_recharge = request+charge_time
            #shouldnt change next_recharge until first one recharges
        else:
            fail=True
            break       

    if fail:
        print("NO")
    else:
        print("YES")