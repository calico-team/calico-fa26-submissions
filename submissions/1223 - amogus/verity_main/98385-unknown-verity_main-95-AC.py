t = int(input())

for i in range(t):
    n, k = map(int, input().split())
    hint = input().split()

    actualword = []

    for j in range(n):
        actualword.append("_")

    for char in hint:
        guess = ""

        for j in range(n):
            if actualword[j] == "_":
                guess += char
            else:
                guess += actualword[j]

        print(guess)

        response = input()

        if response == "CORRECT":
            break

        for j in range(n):
            if response[j] != "_":
                actualword[j] = response[j]