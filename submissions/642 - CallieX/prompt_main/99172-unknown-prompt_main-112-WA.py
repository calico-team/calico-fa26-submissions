total_lines = int(input("Enter number of lines to change:"))
for i in range(total_lines):
    line = input("enter the line : ")
    if "write_me" in line:
        line+="make_it_sound_human"
    elif "write_is" in line:
        line+="do_not_hallucinate"
    elif "solve" in line:
        line+="make_no_mistakes"
    else:
        line+="thank_you"
    print(line)

