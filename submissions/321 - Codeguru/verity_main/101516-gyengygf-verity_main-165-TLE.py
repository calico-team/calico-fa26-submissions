import sys


def main():
    inp = sys.stdin
    num_cases = int(inp.readline())

    for _ in range(num_cases):
        n, k = map(int, inp.readline().split())
        letters = inp.readline().split()

        known = [None] * n

        for _ in letters:
            guess = "".join(known[i] or letter for i, letter in enumerate(letters))
            print(guess)
            sys.stdout.flush()

            response = inp.readline().strip()
            if response == "CORRECT":
                break

            for i, ch in enumerate(response):
                if ch != "_" and known[i] is None:
                    known[i] = ch


main()