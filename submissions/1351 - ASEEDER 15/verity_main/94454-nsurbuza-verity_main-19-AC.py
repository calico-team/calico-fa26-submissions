t = int(input())

for i in range(t):
    n, k = map(int, input().split())
    a = list(input().split())

    underscore = {}
    combine = ["_"] * n

    success = False
    for j in a:
        guess = j * n
        print(guess, flush=True)
        result = input()

        if result == "CORRECT":
            success = True
            break

        for i, z in enumerate(result):
            if z != "_":
                combine[i] = z

    if not success:
        print("".join(combine), flush=True)
        correct = input()