for i in range(int(input())):
    string=input()
    if string.find("write_me") != -1:
        string=string+"make_it_sound_human"
    elif string.find("what_is") != -1:
        string=string+"do_not_hallucinate"
    elif string.find("solve") != -1:
        string=string+"make_no_mistakes"
    else:
        string=string+"thank_you"
    print(string)