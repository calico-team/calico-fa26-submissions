for _ in range(int(input())): 
    x = input() 
    if "write_me" in x or "_write_me_" in x: 
        x += "make_it_sound_human" 
    elif "what_is" in x or "_what_is" in x: 
        x += "do_not_hallucinate" 
    elif "solve" in x or "_solve_" in x: 
        x += "make_no_mistakes" 
    else: 
        x += "thank_you" 
    print(x)

        