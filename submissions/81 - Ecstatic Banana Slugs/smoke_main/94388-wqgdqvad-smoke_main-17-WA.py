tests = int(input())
for i in range(tests):
    data = input().split()
    calls = input().split()
    requests = int(data[0])
    delay = int(data[1])
    time = int(calls[requests-1])
    if time//delay+2 < requests:
        print("no")
    else:
        print("yes")