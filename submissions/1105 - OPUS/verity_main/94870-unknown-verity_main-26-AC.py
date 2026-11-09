def solve():
    t = int(input())

    for _ in range(t):
        length, kinds = map(int, input().split())
        alphabet = input().split()

        matched = {}
        used = set()

        for letter in alphabet[:-1]:
            trial = [
                next((c for c, positions in matched.items()
                      if pos in positions), letter)
                for pos in range(length)
            ]

            print(''.join(trial), flush=True)
            result = input().strip()

            if result == "CORRECT":
                break

            matched[letter] = {
                pos for pos, char in enumerate(result)
                if char == letter
            }
            used.update(matched[letter])

        else:
            final = [alphabet[-1]] * length

            for letter, positions in matched.items():
                for pos in positions:
                    final[pos] = letter

            print(''.join(final), flush=True)
            result = input().strip()

            if result != "CORRECT":
                return


solve()
