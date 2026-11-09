import random
from tkinter import LAST
n = int(input())
for _ in range(n):
    a, b = map(int, input().split())
    done = [[] for _ in range(a)]
    arr = list(input().split())
    while len(arr) < a:
        arr.append(random.choice(arr))
    print("".join(arr))
    lastone = "".join(arr)
    nextone = ""
    while True:
        if nextone != "":
            lastone = nextone
        nextone = input()
        if "_" not in nextone:
            break
        for i in range(len(nextone)):
            if nextone[i] == "_":
                done[i].append(lastone[i])
                rand = str(random.choice(arr))
                while rand in done[i]:
                    rand = str(random.choice(arr))
                nextone = nextone[:i] + rand + nextone[i+1:]
        print(nextone)

