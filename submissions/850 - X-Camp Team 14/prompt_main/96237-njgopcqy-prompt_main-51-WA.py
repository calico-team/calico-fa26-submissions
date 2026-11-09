import sys

lines = sys.stdin.read().splitlines()
if not lines:
    sys.exit()

t = int(lines[0])

for i in range(1, t + 1):
    s = lines[i]
    
    if "write_me" in s:
        print(s + "_make_it_sound_human")
    elif "solve" in s:
        print(s + "_make_no_mistakes")
    elif "what_is" in s:
        print(s + "_do_not_hallucinate")
    else:
        print(s + "_thank_you")