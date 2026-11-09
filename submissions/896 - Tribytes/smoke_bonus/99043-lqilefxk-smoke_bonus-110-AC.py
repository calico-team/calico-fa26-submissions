import sys


def token_stream():
    # Reads one line at a time so memory stays small even for huge inputs.
    for row in sys.stdin:
        for piece in row.split():
            yield piece


def main():
    nxt = token_stream().__next__
    rounds = int(nxt())
    out = []
    for _ in range(rounds):
        total = int(nxt())
        gap = int(nxt())
        free_a = 0   # time when first spent charge is back (0 = ready)
        free_b = 0   # time when second spent charge is back (0 = ready)
        last = 0     # completion time of latest queued recharge
        ok = True
        for _ in range(total):
            now = int(nxt())          # always consume every token
            if not ok:
                continue
            # recharges happen before requests at the same timestamp
            if free_a <= now and free_b <= now:
                pass
            # pick a charge that is ready
            if free_a <= now:
                start = now if now > last else last
                last = start + gap
                free_a = last
            elif free_b <= now:
                start = now if now > last else last
                last = start + gap
                free_b = last
            else:
                ok = False
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out) + "\n")


main()
