import random
n = int(input())
for _ in range(n):
    a, b = map(int, input().split())
    arr = list(input().split())
    while len(arr) < a:
        arr.append(random.choice(arr))
    for s in arr:
        print(s, end = "")
    while True:
        next = input()
        if "_" not in next:
            break
        for i in range(len(next)):
            if next[i] == "_":
                next = next[:i] + str(random.choice(arr)) + next[i+1:]
        print(next)