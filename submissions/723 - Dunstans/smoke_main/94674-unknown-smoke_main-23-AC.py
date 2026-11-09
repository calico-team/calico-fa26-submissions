test_cases = int(input())
for i in range(test_cases):
    usr_input=input().split()
    no_of_smoke_req=int(usr_input[0])
    recharge_time=int(usr_input[1])

    usr_input2=input().split()
    for j in range(len(usr_input2)):
        usr_input2[j]=int(usr_input2[j])
    charges = 2
    ready = 0
    can_use = True

    for j in range(no_of_smoke_req):

        while charges < 2 and ready <= usr_input2[j]:
            charges = charges + 1
            ready = ready + recharge_time
        if charges == 0:
            can_use = False
            break

        if charges == 2:
            ready = usr_input2[j] + recharge_time

        charges = charges - 1
    
    
    if can_use:
        print("YES")
    else:
        print("NO")