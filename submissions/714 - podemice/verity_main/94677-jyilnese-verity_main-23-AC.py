import random

N = int(input())

for _ in range(N):

    done = False
    ln, k = [int(i) for i in input().split(" ")]
    chars = set(input().split(" "))
    curr = "_"* ln
    guess = ""
    arr = [set() for _ in range(ln)]
    while not done:
        for j in range(ln):
            if curr[j] == "_":
                gc = random.choice(list(chars - arr[j]))
                guess += gc
                arr[j].add(gc)
            else:
                guess += curr[j]

        print(guess)

        curr = input()
        guess = ""
        done = curr == 'CORRECT'
