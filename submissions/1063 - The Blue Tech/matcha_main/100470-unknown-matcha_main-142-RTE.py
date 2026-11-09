t = int(input())

for i in range(t):
    line = input().split()
    n = int(line[0])
    k = int(line[1])

    letters = input().split()

    known = ["_"] * n

    for c in letters:
        guess = ""
        for j in range(n):
            if known[j] == "_":
                guess = guess + c
            else:
                guess = guess + known[j]

        print(guess, flush=True)

        reply = input().strip()

        if reply == "CORRECT":
            break

        for j in range(n):
            if reply[j] != "_":
                known[j] = reply[j]