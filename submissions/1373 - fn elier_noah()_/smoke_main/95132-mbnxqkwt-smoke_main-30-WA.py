import sys

input = sys.stdin.readline
test_cases = int(input().strip())

for i in range(test_cases):
    smoke_num, cooldown = input().strip().split(" ")
    times = input().split(" ")

    if (int(times[0]) + int(times[1]) < int(cooldown)):
        print("NO")
    else:
        print("YES")
    