cases = int(input())

for i in range(cases):
    # inp = input().split()
    strlen = int(input().split()[0])
    chars = input().split()

    incr = 0

    guess = [chars[0]] * strlen

    while True:
        print("".join(guess),flush = True)

        correction = input()

        if correction == "CORRECT":
            break

        incr += 1
        for i,j in enumerate(correction):
            if j == "_":
                guess[i] = chars[incr]