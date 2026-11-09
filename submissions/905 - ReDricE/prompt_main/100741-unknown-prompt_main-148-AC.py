import sys
input = lambda : sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    a = input()
    if "write_me" in a:
        print(a + "make_it_sound_human")
    elif "what_is" in a:
        print(a + "do_not_hallucinate")
    elif "solve" in a:
        print(a + "make_no_mistakes")
    else:
        print(a + "thank_you")