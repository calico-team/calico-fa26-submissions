p = int(input())
for i in range(p):
    string = input()
    if(string.find("what_is")!=-1):
        print(string+"do_not_hallucinate")
    elif(string.find("write_me")!=-1):
        print(string+"make_it_sound_human")
    elif(string.find("solve")!=-1):
        print(string+"make_no_mistakes")
    else:
        print(string+"thank_you")
    