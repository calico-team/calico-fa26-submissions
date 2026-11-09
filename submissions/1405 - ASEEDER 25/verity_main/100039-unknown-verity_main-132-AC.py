import sys


def solve():
    input = sys.stdin.readline
    test_cases = int(input())

    for _ in range(test_cases):
        n, k = map(int, input().split())
        alphabet = input().split()
        answer = [""] * n

        # Test each character except the last one with a repeated-character
        # guess. Any positions still unknown must use the final character.
        for index, char in enumerate(alphabet):
            if index == k - 1:
                for position in range(n):
                    if answer[position] == "":
                        answer[position] = char
                guess = "".join(answer)
            else:
                guess = char * n

            print(guess, flush=True)
            response = input().strip()

            if response == "CORRECT":
                break

            for position, value in enumerate(response):
                if value != "_":
                    answer[position] = value


if __name__ == "__main__":
    solve()
