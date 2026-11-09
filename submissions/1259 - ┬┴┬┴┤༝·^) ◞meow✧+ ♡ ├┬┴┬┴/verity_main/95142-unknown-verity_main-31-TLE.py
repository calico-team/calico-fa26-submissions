import sys
inp = [line.strip() for line in sys.stdin]

for _ in range(int(input())):
    n, k = map(int, input().split()) # len seq, num types ities
    a = input().split() # letters names ities
    ans = ["?" for _ in range(n)]
    corr = False
    for c in a:
        print(c*n, flush=True) # spam each fully
        w = input()
        if w == "CORRECT":
            corr = True
            break
        for i, d in enumerate(w):
            if d != "_":
                ans[i] = d
    if not corr:
        print("".join(ans), flush=True)
    input()
