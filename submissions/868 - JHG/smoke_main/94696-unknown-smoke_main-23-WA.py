tests = int(input())
for i in range(tests):
    numRequests, recharge = map(int, input().split())
    requests = list(map(int, input().split()))

    charge1disposed = requests[0]
    charge2disposed = -10000000
    printed = False

    for j in range(1, numRequests):
        time = requests[j]
        success = False

        charger1_busy = (time - charge1disposed < recharge)
        charger2_busy = (time - charge2disposed < recharge)

        if not charger1_busy and not charger2_busy:
            charge1disposed = time
            success = True

        if not success:
            print('No')
            printed = True
            break

    if not printed:
        print('Yes')
