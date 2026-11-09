import math
data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    input_requests = map(int, input().split())
    data.append([time,input_requests])

for charge_time,requests in data:
    charges = 2
    last_request = 0
    fail = False
    for request in requests:
        charge_add = math.floor(request/charge_time) - math.floor(last_request/charge_time)
        charges = max((charges+charge_add), 2)
        if charges>0:
            charges-=1
            last_request = request
        else:
            fail = True
    if fail:
        print("NO")
    else:
        print("YES")