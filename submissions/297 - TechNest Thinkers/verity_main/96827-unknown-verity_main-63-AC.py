import sys
import random


def play(n, letters, ask):
    """Hidden string guess karta hai. (guesses ki tadad, CORRECT mila ya nahi) return karta hai."""
    known = ["_"] * n
    count = 0
    for c in letters:
        guess = "".join(k if k != "_" else c for k in known)
        count += 1
        resp = ask(guess)
        if resp == "CORRECT":
            return count, True
        for i, ch in enumerate(resp):
            if ch != "_":
                known[i] = ch
    
    
    if "_" not in known:
        count += 1
        if ask("".join(known)) == "CORRECT":
            return count, True
    return count, False


def main():
    def ask(guess):
        print(guess, flush=True)
        return input().strip()

    t = int(input())
    for _ in range(t):
        n, k = map(int, input().split())
        letters = input().split()
        play(n, letters, ask)


def self_test():
   
    worst = 0
    for _ in range(2000):
        k = random.randint(1, 26)
        letters = random.sample("ABCDEFGHIJKLMNOPQRSTUVWXYZ", k)
        n = random.randint(1, 100)
        hidden = "".join(random.choice(letters) for _ in range(n))

        def ask(guess):
            if guess == hidden:
                return "CORRECT"
            return "".join(g if g == h else "_" for g, h in zip(guess, hidden))

        used, solved = play(n, letters, ask)
        assert solved, "CORRECT nahi mila"
        assert used < 100
        worst = max(worst, used)
    print("OK, 2000 test pass. Sab se zyada guesses:", worst)


if len(sys.argv) > 1 and sys.argv[1] == "test":
    self_test()
else:
    main()