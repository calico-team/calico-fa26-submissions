info = input()
info_list = info.strip().split(" ")
requests = input()
requests_list = requests.strip().split()
smoke_request_number = int(info_list[0])
smoke_recharge_time = int(info_list[1])
charges = 2
for i in range(0, len(requests_list)):
    if i + 1 == 1:
        charges -= 1
        smoke_request_number -= 1
    elif i >= 1:
        time_after_use = int(requests_list[i]) - int(requests_list[i - 1])
        if time_after_use >= smoke_recharge_time:
            smoke_request_number -= 1
        elif time_after_use < smoke_recharge_time and charges > 0:
            smoke_request_number -= 1
            charges -= 1
        else:
            print("NO")
            break
if smoke_request_number <= 0:
    print("YES")