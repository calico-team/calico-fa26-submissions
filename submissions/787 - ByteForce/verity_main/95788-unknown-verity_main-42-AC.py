t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    a = input().split()

    word = ["_"] * n

    for letter in a:
        guess = ""

        for i in range(n):
            if word[i] == "_":
                guess = guess + letter
            else:
                guess = guess + word[i]

        print(guess, flush=True)

        result = input().strip()

        if result == "CORRECT":
            break

        for i in range(n):
            if result[i] != "_":
                word[i] = result[i]
