solverkk=int(input())
for i in range(solverkk):
    kon=input().strip()
    
    if "write_me" in kon:
        kon+="make_it_sound_human"
        
    elif "what_is" in kon: 
        kon+="do_not_hallucinate"
    elif "solve" in kon:
        
        kon+="make_no_mistakes"
    else:
        kon+="thank_you"
    print(kon)