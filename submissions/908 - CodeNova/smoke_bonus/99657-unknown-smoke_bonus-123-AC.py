
import sys


def int_stream():
    """Yield integers lazily, one line at a time ( low memory)."""
    for line in sys.stdin.buffer:
        for token in line.split():
            yield int(token)



def main():
    it = int_stream()

    try:
        t = next(it)
    except StopIteration:
        return

    out = []

    for _ in range(t):
        n = next(it)
        r = next(it)

        pending = []
        possible = True

        for j in range(n):
            a = next(it)

            if pending and pending[0] <= a:
                pending.pop(0)
                if pending and pending[0] <= a:
                    pending.pop(0)

            if len(pending) == 2:
                possible = False
                for _ in range(n - j - 1):
                    next(it)
                break


            start = pending[-1] if pending else a
            pending.append(start + r)

        out.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()

        