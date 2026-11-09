def solve(N: int, K: int, A: list[str]) -> None:
    ans = ['?']*N
    for char in A:
        guess=""
        for i in range(N):
            if ans[i] == '?':
                guess = guess+char
            else:
                guess = guess+ans[i]
        print_guess(guess)
        response = read_string()
        if response == "CORRECT":
            return
        for i in range(N):
            if response[i] != '_':
                ans[i] = response[i]
                
def read_string():
    s = input()
    return s

def print_guess(guess):
    print(guess, flush=True)

def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
