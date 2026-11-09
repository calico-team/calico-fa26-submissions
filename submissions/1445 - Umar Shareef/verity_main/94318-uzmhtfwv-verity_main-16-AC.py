import sys


def solve():
    inp = sys.stdin
    out = sys.stdout

    t = int(inp.readline().strip())
    for _ in range(t):
        # read N and K, skipping any blank lines
        line = inp.readline()
        while line.strip() == '':
            line = inp.readline()
        n, k = map(int, line.split())

        # read the K possible characters (given space-separated)
        chars = []
        while len(chars) < k:
            for tok in inp.readline().split():
                if len(tok) == 1:
                    chars.append(tok)
                else:
                    chars.extend(tok)
        chars = chars[:k]

        known = [''] * n  # known[i] = character found for position i
        done = False

        # Try each character except the last one. A guess fills every
        # still-unknown position with that character, and the feedback
        # tells us exactly which positions really hold that character.
        for c in chars[:-1]:
            guess = ''.join(known[i] if known[i] else c for i in range(n))
            out.write(guess + '\n')
            out.flush()
            resp = inp.readline().strip()
            if resp == 'CORRECT':
                done = True
                break
            for i in range(n):
                if resp[i] != '_':
                    known[i] = resp[i]

        if not done:
            # Whatever is still unknown must be the last character.
            last = chars[-1]
            guess = ''.join(known[i] if known[i] else last for i in range(n))
            out.write(guess + '\n')
            out.flush()
            inp.readline()  # should be CORRECT


if __name__ == '__main__':
    solve()
