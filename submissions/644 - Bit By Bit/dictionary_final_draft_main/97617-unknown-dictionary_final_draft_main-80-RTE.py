def solveProblem():
    testCaseCount = int(input())

    for _ in range(testCaseCount):
        requestCount, rechargeSeconds = map(int, input().split())
        requestTimes = list(map(int, input().split()))

        availableCharges = 2
        pendingRecharges = []
        possible = True

        for time in requestTimes:
            while len(pendingRecharges) > 0 and pendingRecharges[0] <= time:
                pendingRecharges.pop(0)
                if availableCharges < 2:
                    availableCharges += 1

            if availableCharges == 0:
                possible = False
                break

            availableCharges -= 1

            if len(pendingRecharges) == 0:
                nextRechargeTime = time + rechargeSeconds
            else:
                nextRechargeTime = pendingRecharges[-1] + rechargeSeconds
            pendingRecharges.append(nextRechargeTime)

        if possible:
            print("YES")
        else:
            print("NO")


if __name__ == "__main__":
    solveProblem()
