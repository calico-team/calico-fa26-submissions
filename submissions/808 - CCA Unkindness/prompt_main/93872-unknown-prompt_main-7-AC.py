# Source: https://usaco.guide/general/io

def cool_func():
    cool_string = input()
    if "write_me" in cool_string:
        print(cool_string + "make_it_sound_human")
    elif "what_is" in cool_string:
        print(cool_string + "do_not_hallucinate")
    elif "solve" in cool_string:
        print(cool_string + "make_no_mistakes")
    else:
        print(cool_string + "thank_you")

t = int(input())
for i in range(t):
    cool_func()
    