import sys


def make_guess(guess_word):
    sys.stdout.write(guess_word + "\n")
    sys.stdout.flush()
    return sys.stdin.readline().strip()


def main():
    first_line = sys.stdin.readline()
    if not first_line.strip():
        return

    total_test_cases = int(first_line)

    for _ in range(total_test_cases):
        line = sys.stdin.readline()
        while line.strip() == "":
            line = sys.stdin.readline()

        parts = line.split()
        hidden_length = int(parts[0])
        alphabet_size = int(parts[1])

        alphabet_line = sys.stdin.readline()
        while alphabet_line.strip() == "":
            alphabet_line = sys.stdin.readline()

        alphabet_list = alphabet_line.split()

        secret_word = ["?"] * hidden_length
        already_solved = False

        for letter in alphabet_list:
            guess_word = letter * hidden_length
            reply = make_guess(guess_word)

            if reply == "CORRECT":
                already_solved = True
                break

            for position in range(hidden_length):
                if reply[position] != "_":
                    secret_word[position] = reply[position]

        if not already_solved:
            final_guess = "".join(secret_word)
            make_guess(final_guess)


if __name__ == "__main__":
    main()