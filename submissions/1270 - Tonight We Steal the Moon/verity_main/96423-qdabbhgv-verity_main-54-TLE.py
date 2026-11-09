import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    idx = 0
    T = int(data[idx])
    idx += 1

    for _ in range(T):
        N = int(data[idx])
        K = int(data[idx + 1])
        idx += 2

        allowed = data[idx:idx + K]
        idx += K

        current_guess = [allowed[0]] * N

        ans = list(allowed[0] * N)

        pass


def interactive_solve():
    import sys
    def input_line():
        return sys.stdin.readline().strip()

    line = input_line()
    if not line:
        return
    T = int(line)

    for _ in range(T):
        parts = input_line().split()
        N = int(parts[0])
        K = int(parts[1])
        allowed = input_line().split()

        guess = [allowed[0]] * N
        print("".join(guess))
        sys.stdout.flush()

        response = input_line()
        if response == "CORRECT":
            continue



if __name__ == '__main__':
    interactive_solve()
