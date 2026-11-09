T = int(input())
for i in range(T): 
    (N, K) = tuple(map(int, input().strip().split()))
    final = list("_" * N)
    characters = list(input().strip().split())
    for character in characters:
        print(character * N)
        hint = list(input().strip())
        for idx, character in enumerate(hint):
            if final[idx] == "_":
                final[idx] = character
    print("".join(final))
