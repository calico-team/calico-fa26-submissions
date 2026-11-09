def solve(N: int, K: int, A: list[str]) -> None:
	ans = ['-'] * N
	for char in A:
		print_guess(char * N)
		resp = read_string()
		if resp == "CORRECT":
			return
		for i in range(len(resp)):
			if resp[i] != '_':
				ans[i] = resp[i]
	print_guess(''.join(ans))
	x = read_string()
def read_string():
    """
    Reads a single string from standard input.
    """
    s = input()
    return s

def print_guess(guess):
    """
    Prints a guess to standard output and flushes the output stream buffer.
    """
    print(guess, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
