T = int(input())

for i in range(T):
    N, K = map(int, input().split())
    letters = input().split()

    guess = ["" for j in range(N)]

    gotcha = False
    for letter in letters[:-1]:
        print(letter * N, flush=True)

        resp = input()
        if resp == "CORRECT":
            gotcha=True
            break
        for ind, l in enumerate(resp):
            if l != "_":
                guess[ind] = l

    for i, c in enumerate(guess):
        if c == "":
            guess[i] = letters[-1]

    if not gotcha:
        print("".join(guess), flush=True)
        resp = input()

