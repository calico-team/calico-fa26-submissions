tests = int(input())
for i in range(tests):
    n,k = map(int, input().split())
    letters = input().split()
    known = ["_"]*n
    for letter in letters:
        guess = ""
        for c in known:
            if c == "_":
                guess = guess + letter
            else:
                guess = guess + c
        print(guess,flush=True)
        reply = input().strip()
        if reply == "CORRECT":
            break
        for j in range(n):
            if reply[j] != "_":
                known[j] = reply[j]
