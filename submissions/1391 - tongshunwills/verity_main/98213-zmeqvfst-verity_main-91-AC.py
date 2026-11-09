import sys
#gues one letter
def bennitybennity(n, chars, guess):
    result = ["_"] * n
    for letter in chars:
        current = ""
        for i in range(n):
            if result[i] == "_":
                current += letter
            else:
                current += result[i]
        response = guess(current)
        if response == "CORRECT":
            return
        for i in range(n):
            if response[i] != "_":
                result[i] = response[i]


def main():
    def read_input():
        line = sys.stdin.readline().strip()
        while line == "":
            line = sys.stdin.readline().strip()
        return line

#/
    def guess(word):
        print(word, flush=True)
        return read_input()
    t = int(read_input())
    for _ in range(t):
        n, k = map(int, read_input().split())
        chars = read_input().split()
        bennitybennity(n, chars, guess)


if __name__ == "__main__":
    main()
