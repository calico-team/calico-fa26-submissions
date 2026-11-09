import sys

def solve() -> None:
    data = sys.stdin.read().strip().split()
    if not data:
        return
    t = int(data[0])
    ss = data[1:1 + t]

    # unique way: no if/elif chain — one lookup table + a generator
    # that picks the first suffix whose trigger is hiding inside S.
    table = (
        ("write_me", "make_it_sound_human"),
        ("what_is", "do_not_hallucinate"),
        ("solve", "make_no_mistakes"),
    )

    out = []
    for s in ss:
        suffix = next((v for k, v in table if k in s), "thank_you")
        out.append(s + suffix)

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()