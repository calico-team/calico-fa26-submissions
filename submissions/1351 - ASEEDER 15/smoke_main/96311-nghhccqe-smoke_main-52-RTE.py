T = int(input())
for i in range(T):
    smokeRstr = []
    flag = 0
    smokeR, rechargeT = map(int, input().split())
    for i in range(smokeR):
        smokeRstr.append('0')

    '''
    for i in range(len(smokeRstr)):
        if int(smokeRstr[i + 1]) - int(smokeRstr[i]) >= rechargeT:
            print('NO')
            flag = 1
            break
        else:
            flag = 0
            continue
    if flag == 0:
        print('YES')
    '''
