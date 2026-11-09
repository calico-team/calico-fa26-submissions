import sys

input_data = sys.stdin.read().split()
t = int(input_data[0])

for i in range(1, t + 1):
    s = input_data[i]
    
    if "write_me" in s:
        print(s + "_make_it_sound_human")
    elif "solve" in s:
        print(s + "_make_no_mistakes")
    elif "what_is" in s:
        print(s + "_do_not_hallucinate")
    else:
        print(s + "_thank_you")