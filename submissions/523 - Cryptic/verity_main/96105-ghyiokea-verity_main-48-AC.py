T = int(input())

for _ in range(T):
    N, K = list(map(int, input().split()))

    A = input().split()

    out = [""] * N
    found = False
    for char in A:
        print(char * N, flush=True)
        clue = input()

        if clue == "CORRECT":
            found = True
            break

        for i, idk in enumerate(clue):
            if idk == char:
                out[i] = char

    if not found:
        print("".join(out), flush=True)
        yay = input()