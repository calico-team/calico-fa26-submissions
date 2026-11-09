T = int(input())
for i in range(T): 
    (N, K) = tuple(map(int, input().strip().split()))
    final = ["_" for i in range(N)]
    finalstr = ""
    characters = input().strip().split()
    for character in characters:
        print(character * N)
        hint = input().strip()
        if hint == "CORRECT":
            break
        else:
            hint = list(hint)
        for idx, character in enumerate(hint):
            if final[idx] != character:
                final[idx] = character
    finalstr = "".join(final)
    print(finalstr)