solverkk=int(input())
for i in range(solverkk):
    kon=input().strip()
    
    if "write_me_a_rank" in kon:
        kon+="make_it_sound_human"
        
    elif "what_is_" in kon: 
        kon+="do_not_hallucinate"
    elif "solve_all_of_the" in kon:
        
        kon+="make_no_mistakes"
    else:
        kon+="thank_you"
    print(kon)