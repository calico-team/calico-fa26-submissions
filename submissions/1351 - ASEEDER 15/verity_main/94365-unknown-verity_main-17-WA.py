t = int(input())

for i in range(t):
    n, k = map(int, input().split())
    a = list(input().split())

    underscore = {}
    combine = ["_"] * n
    for j in a:
        guess = j * n
        print(guess, flush=True)
        result = input()

        if result == "CORRECT":
            break

        for i, z in enumerate(result):
            if z != "_":
                combine[i] = z

    print("".join(combine), flush=True)
    correct = input()