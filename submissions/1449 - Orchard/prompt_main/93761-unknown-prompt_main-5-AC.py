

lines = int(input())

for i in range(lines):
    line = input()
    if "write_me" in line: 
        print(line + "make_it_sound_human")
    elif "what_is" in line:
        print(line + "do_not_hallucinate")
    elif "solve" in line:
        print(line + "make_no_mistakes")
    else:
        print(line + "thank_you")
