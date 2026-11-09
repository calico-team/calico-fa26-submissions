import math
data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    input_requests = input().split()
    input_requests = [int(item) for item in input_requests]
    data.append([time,input_requests])

for charge_time,requests in data:
    charges = 2
    last_request = 0
    fail = False
    for request in requests:
        charge_add = math.floor((request-last_request)/charge_time)
        if charges+charge_add<=2:
            charges+=charge_add
        # if request-last_request>=charge_time and charges<2:
        #     charges+=(request-last_request)//charge_time
        if charges>0:
            charges-=1
            last_request = request
        else:
            fail = True
    if fail:
        print("NO")
    else:
        print("YES")