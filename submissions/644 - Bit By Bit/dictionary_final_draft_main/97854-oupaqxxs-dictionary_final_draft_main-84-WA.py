import sys


def solveProblem():
    tokens = sys.stdin.read().split()
    pos = 0
    testCaseCount = int(tokens[pos])
    pos += 1
    answers = []

    for _ in range(testCaseCount):
        requestCount = int(tokens[pos])
        pos += 1
        rechargeSeconds = int(tokens[pos])
        pos += 1
        requestTimes = []
        for _ in range(requestCount):
            requestTimes.append(int(tokens[pos]))
            pos += 1
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
            answers.append("YES")
        else:
            answers.append("NO")

    sys.stdout.write("\n".join(answers) + "\n")


if __name__ == "__main__":
    solveProblem()
