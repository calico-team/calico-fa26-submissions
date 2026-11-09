T = int(input())
for i in range(T):
    done = False
    (N, K) = tuple(map(int, input().strip().split()))
    final = list("_" * N)
    characters = list(input().strip().split())
    for character in characters:
        print(character * N)
        hint = input().strip()
        if hint == "CORRECT":
            done = True
            break
        else:
            hint = list(hint)
        for idx, character in enumerate(hint):
            if final[idx] == "_":
                final[idx] = character
    if not done:
        print("".join(final))
        input()
