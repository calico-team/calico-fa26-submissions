data = []
for _ in range(int(input())):
    time = int(input().split()[1])
    request = input().split()
    request = [int(item) for item in request]
    data.append([time,request])

for charge_time,requests in data:
    charges = 2
    last_request = 0
    fail = False
    for request in requests:
        if request-last_request>=charge_time:
            charges+=1
        if charges>0:
            charges-=1
            last_request = request
        else:
            fail = True
    if fail:
        print("NO")
    else:
        print("YES")