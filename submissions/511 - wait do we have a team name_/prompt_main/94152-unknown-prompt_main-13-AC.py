import sys

input = sys.stdin.readline
t = int(input())
s = [input() for _ in range(t)]
for new in s:
    new = new.replace("\n", "")
    if "write_me" in new:
        print(new + "make_it_sound_human")
    elif "what_is" in new:
        print(new + "do_not_hallucinate")
    elif "solve" in new:
        print(new + "make_no_mistakes")
    else:
        print(new + "thank_you")
