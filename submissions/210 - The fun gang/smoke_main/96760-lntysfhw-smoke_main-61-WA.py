import math
data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    input_requests = input().split()
    input_requests = [int(item) for item in input_requests]
    data.append([time,input_requests])

for charge_time,requests in data:
    charges = 2
    charges_added = 0
    charge_add = 0
    fail = False
    for request in requests:


        
        charge_add = math.floor(request/charge_time)-charges_added
        charges_added = math.floor(request/charge_time)
        charges = min(2,charges+charge_add)




        # if charges+charge_add>2:
        #     # charges_added += 2-charges
        #     charges=2
        # else:
        #     charges+=charge_add
        #     # charges_added += charge_add

        if charges>0:
            charges-=1
        else:
            fail = True
    if fail:
        print("NO")
    else:
        print("YES")