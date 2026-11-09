test_cases = int(input())

for case in range(test_cases):
    n, k = map(int, input().split())
    letters = input().split()
    guess = ["_"] * n

    for letter in letters:
        for position in range(n):
            if guess[position] == "_":
                guess[position] = letter

        print("".join(guess))
        response = input().strip()

        if response == "CORRECT":
            break

        guess = list(response)
