import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    out = []
    for s in data[1:t + 1]:
        if "write_me" in s:
            out.append(s + "make_it_sound_human")
        elif "what_is" in s:
            out.append(s + "do_not_hallucinate")
        elif "solve" in s:
            out.append(s + "make_no_mistakes")
        else:
            out.append(s + "thank_you")
    sys.stdout.write("\n".join(out) + "\n")


main()
