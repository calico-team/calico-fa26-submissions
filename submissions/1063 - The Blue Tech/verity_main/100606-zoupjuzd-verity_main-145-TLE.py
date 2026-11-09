def read_line():
    line = input().strip()
    while line == "":
        line = input().strip()
    return line


t = int(read_line())

all_n = []
all_letters = []

for i in range(t):
    line = read_line().split()
    all_n.append(int(line[0]))
    all_letters.append(read_line().split())

for i in range(t):
    n = all_n[i]
    letters = all_letters[i]

    known = ["_"] * n

    for c in letters:
        guess = ""
        for j in range(n):
            if known[j] == "_":
                guess = guess + c
            else:
                guess = guess + known[j]

        print(guess, flush=True)

        reply = read_line()

        if reply == "CORRECT":
            break

        for j in range(n):
            if reply[j] != "_":
                known[j] = reply[j]