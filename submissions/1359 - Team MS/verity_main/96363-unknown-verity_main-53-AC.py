import sys

def solve_game():
    read_input = sys.stdin.readline
    test_cases = int(read_input())

    for case_number in range(test_cases):
        word_length, alphabet_size = map(int, read_input().split())
        possible_letters = read_input().split()

        confirmed_letters = [None] * word_length
        candidate_position = [0] * word_length

        while True:
            current_guess = ""

            for position in range(word_length):
                if confirmed_letters[position] is not None:
                    current_guess += confirmed_letters[position]
                else:
                    current_guess += possible_letters[candidate_position[position]]

            print(current_guess, flush=True)

            feedback = read_input().strip()

            if feedback == "CORRECT":
                break

            for position in range(word_length):
                if feedback[position] != '_':
                    confirmed_letters[position] = feedback[position]
                elif confirmed_letters[position] is None:
                    candidate_position[position] += 1


if __name__ == "__main__":
    solve_game()