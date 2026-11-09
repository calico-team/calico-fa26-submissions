import math
data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    input_requests = input().split()
    input_requests = [int(item) for item in input_requests]
    data.append([time,input_requests])

for charge_time,requests in data:
    # charges = 2
    # charges_added = 0
    # charge_add = 0
    # last_request = 0
    # fail = False
    # for request in requests:










    #     charges+=math.floor((request-last_request)/charge_time)
    #     # charge_add = math.floor(request/charge_time)-charges_added
    #     # charges_added = math.floor(request/charge_time)
    #     charges = min(2,charges)




    #     # if charges+charge_add>2:
    #     #     # charges_added += 2-charges
    #     #     charges=2
    #     # else:
    #     #     charges+=charge_add
    #     #     # charges_added += charge_add

    #     if charges>0:
    #         charges-=1
    #         last_request = request
    #     else:
    #         fail = True
    #         break

    charges=2
    next_recharge = None
    fail = False
    for request in requests:
        while next_recharge is not None and request>=next_recharge:
            charges+=1
            if charges==2:
                next_recharge = None
            else:
                next_recharge+=charge_time


        # if next_recharge is not None and request>=next_recharge:
        #     charges+=1
        #     next_recharge = None

        if charges>0:
            charges-=1
            next_recharge = request+charge_time
        else:
            fail=True
            break





    if fail:
        print("NO")
    else:
        print("YES")