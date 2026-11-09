T = int(input())

for i in range(T):
    N, K = map(int, input().split())
    letters = input().split()

    guess = ["" for j in range(100)]

    for letter in letters:
        print(letter * 100)

        resp = input()
        if resp == "CORRECT":
            break
        for ind, l in enumerate(resp):
            if l != "_":
                guess[ind] = l

    print("".join(guess))
    resp = input()

