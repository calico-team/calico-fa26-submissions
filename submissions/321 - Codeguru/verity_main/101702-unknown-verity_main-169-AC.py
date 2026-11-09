import sys


def main():
    stdin = sys.stdin

    num_cases = int(stdin.readline())

    for _ in range(num_cases):
        n, k = map(int, stdin.readline().split())
        letters = stdin.readline().split()

        # Track which positions have been confirmed so far.
        known = [None] * n

        for letter in letters:
            # Fill unknown positions with the current guess letter.
            guess = "".join(known[i] or letter for i in range(n))
            print(guess)
            sys.stdout.flush()

            response = stdin.readline().strip()

            if response == "CORRECT":
                break

            # Learn any newly revealed correct characters.
            for i, ch in enumerate(response):
                if ch != "_" and known[i] is None:
                    known[i] = ch


if __name__ == "__main__":
    main()