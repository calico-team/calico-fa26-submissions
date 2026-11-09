# Source: https://usaco.guide/general/io
import sys

data = sys.stdin.read().split()
t = int(data[0])

for s in data[1:1 + t]:
    if "write_me" in s:
        suffix = "make_it_sound_human"
    elif "what_is" in s:
        suffix = "do_not_hallucinate"
    elif "solve" in s:
        suffix = "make_no_mistakes"
    else:
        suffix = "thank_you"

    print(s + suffix)