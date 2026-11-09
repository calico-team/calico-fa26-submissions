import sys

input = sys.stdin.readline
test_cases = int(input().strip())

for i in range(test_cases):
    line = input().strip()
    if "write_me" in line:
        line += "make_it_sound_human"
    elif "what_is" in line:
        line += "do_not_hallucinate"
    elif "solve" in line:
        line += "make_no_mistakes"
    else:
        line += "thank_you"

    print(line)