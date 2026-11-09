import sys

def solve() -> None:
    inp = sys.stdin
    out = sys.stdout
    t_line = inp.readline()
    if not t_line:
        return
    t = int(t_line.strip())
    for _ in range(t):
        # read N K skipping empty lines
        line = inp.readline()
        while line is not None and line.strip() == "":
            line = inp.readline()
        if not line:
            return
        parts = line.strip().split()
        while len(parts) < 2:
            parts += inp.readline().strip().split()
        n = int(parts[0])
        k = int(parts[1])
        # read K characters
        chars = []
        while len(chars) < k:
            line = inp.readline()
            if not line:
                break
            chars.extend(line.strip().split())
        chars = chars[:k]

        ans = ['?'] * n
        found = False
        for ch in chars:
            guess = ch * n
            out.write(guess + "\n")
            out.flush()
            resp = inp.readline()
            if not resp:
                return
            resp = resp.strip()
            if resp == "CORRECT":
                found = True
                break
            # resp length n, '_' or ch
            for i in range(n):
                if resp[i] != '_':
                    ans[i] = resp[i]
            # early exit if all found
            if all(c != '?' for c in ans):
                break
        if found:
            continue
        final = "".join(ans)
        out.write(final + "\n")
        out.flush()
        resp = inp.readline()
        # should be CORRECT
        # if not, keep trying (fallback) - should not happen
        while resp and resp.strip() != "CORRECT":
            # if judge gave pattern, update
            r = resp.strip()
            for i in range(n):
                if r[i] != '_':
                    ans[i] = r[i]
            final = "".join(ans)
            out.write(final + "\n")
            out.flush()
            resp = inp.readline()

if __name__ == "__main__":
    solve()