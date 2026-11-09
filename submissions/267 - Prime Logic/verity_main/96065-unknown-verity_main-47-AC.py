def solve(N: int, K: int, A: list[str]) -> None:
    matched = "_" * N
    for letter in A:
        letters = []
        for ch in matched:
            if ch == "_":
                letters.append(letter)
            else:
                letters.append(ch)
        guess = "".join(letters)
        print_guess(guess)
        
        matched = read_string()
        if matched == "CORRECT":
            return



def read_string():
    return input()

def print_guess(guess):
    print(guess, flush=True)


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()
        solve(N, K, A)

if __name__ == "__main__":
    main()