
def smokebombs():
    #Variables
    smokeRequests, recharge = input().split()
    smokeRequests, recharge = int(smokeRequests), int(recharge) #making it a int
    times = input().split()

    for i in range(len(times)): #making all the values into integers
        times[i] = int(times[i])

    startingTime = 0
    yesAmount = 0


    #Code
    for i in range(len(times)):
        if times[i] - startingTime >= recharge:
            yesAmount += 1
            startingTime = times[i]

    if yesAmount == smokeRequests:
        print("Yes")
    else:
        print("No")

testCases = int(input())

for i in range(testCases):
    smokebombs()