t = int(input())

for i in range(t):
    n, k = map(int, input().split())
    a = list(input().split())

    underscore = {}
    combine = []
    for j in a:
        guess = j * n
        result = list(input())

        if str(result) == "CORRECT":
            break

        for i, z in enumerate(result):
            if z != "_":
                combine.append(z)

                if i in underscore:
                    underscore[i] += 1
                else:
                    underscore.setdefault(i, 0)

    for key in underscore:
        if underscore[key] == 4:
            combine.insert(key-1, "_")

    print("".join(combine))
    correct = input()