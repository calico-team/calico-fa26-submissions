n = int(input())
while n:
    n -= 1
    s = input()
    if s.find("write_me") != -1:
        print (s + "make_it_sound_human")
    elif s.find("what_is") != -1:
        print (s + "do_not_hallucinate")
    elif s.find("solve") != -1:
        print (s + "make_no_mistakes")
    else:
        print (s + "thank_you")