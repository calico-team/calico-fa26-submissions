import sys


def solve():
    # Read all inputs at once for speed
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    t = int(input_data[0])
    idx = 1

    for _ in range(t):
        n = int(input_data[idx])
        k = int(input_data[idx + 1])
        idx += 2

        chars = input_data[idx:idx + k]
        idx += k

        # Start with the first allowed character for every position
        guess = [chars[0]] * n

        while True:
            # Send the guess to the judge
            print("".join(guess))
            sys.stdout.flush()

            # Read the judge's response
            res = sys.stdin.readline().strip()
            if res == "CORRECT":
                break

            # Update the guess based on the judge's hint
            for i in range(n):
                if res[i] != '_':
                    # Lock in the correct character
                    guess[i] = res[i]
                else:
                    # Try the next character in the allowed list
                    curr = guess[i]
                    nxt = chars[(chars.index(curr) + 1) % k]
                    guess[i] = nxt


if __name__ == '__main__':
    solve()