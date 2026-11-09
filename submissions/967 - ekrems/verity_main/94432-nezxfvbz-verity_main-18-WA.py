def solve(N: int, K: int, A: list[str]) -> None:
    cevap = [None] * N
    for c in A:
        guess = ''.join(x if x else c for x in cevap)
        print_guess(guess)
        res = read_string().strip()
        if res == "CORRECT":
            return
        for i, ch in enumerate(res):
            if ch != '_':
                cevap [i] = ch