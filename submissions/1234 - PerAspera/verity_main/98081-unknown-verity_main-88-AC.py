t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    let = map(str, input().split())
    word = ["_"] * n
    out = ["_"] * n
    for letter in let:
        for i in range(n):
            if out[i] == "_":
                word[i] = letter


        print("".join(word), flush = True)

        answer = input()
        if  answer == "CORRECT":
            break

        for i, l in enumerate(answer):
            if l != "_":
                out[i] = l
                word[i] = l
