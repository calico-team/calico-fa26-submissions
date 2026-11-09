import sys

t_cases = sys.stdin.readline().strip()
t = int(t_cases)

for i in range(t):
    s = sys.stdin.readline().strip()
    

    if "write_me" in s:
        r = s+"make_it_sound_human"
    elif "what_is" in s:
        r = s+"do_not_hallucinate"
    elif "solve" in s:
        r = s+"make_no_mistakes"
    else:
        r = s+"thank_you"
        


    print(r)