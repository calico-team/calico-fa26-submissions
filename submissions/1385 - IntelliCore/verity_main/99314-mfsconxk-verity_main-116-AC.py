T = int(input())

for i in range(T):
    n, k = map(int, input().split())
    a = input().split()

    answer = ["?"] * n

    for ch in a:
        guess = ""

        for i in range(n):
            if answer[i] == "?":
                guess += ch
            else:
                guess += answer[i]

        print(guess, flush=True)

        result = input().strip()

        if result == "CORRECT":
            break

        for i in range(n):
            if result[i] != "_":
                answer[i] = result[i]

        if "?" not in answer:
            print("".join(answer), flush=True)
            result = input().strip()
            break