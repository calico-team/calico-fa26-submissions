def solve(N: int, K: int, A: list[str]) -> None:
 
    known = [''] * N
    for c in A:
     
        g = ''.join(known[i] or c for i in range(N))
        print_guess(g)
        r = read_string().strip()
        if r == "CORRECT":
            return
        for i in range(N):
            if r[i] != '_':
                known[i] = r[i]

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