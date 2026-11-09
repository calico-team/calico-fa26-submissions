tnt = int(input())

for i in range(tnt):
    a = input()
    
    
    if "write_me" in a:
        a = a+ "make_it_sound_human"
    elif "what_is" in a:
        a = a + "do_not_hallucinate"
    elif "solve" in a:
        a = a + "make_no_mistake"
    else:
        a = a + "thank_you"
    
    
    
    print()