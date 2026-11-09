import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    alphabet = input().split()

    known = ["_"] * n

    for letter in alphabet:
        guess = []

        for i in range(n):
            if known[i] == "_":
                guess.append(letter)
            else:
                guess.append(known[i])

        print("".join(guess), flush=True)
        response = input().strip()

        if response == "CORRECT":
            break

        for i in range(n):
            if response[i] != "_":
                known[i] = response[i]