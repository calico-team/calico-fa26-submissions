
def change_the_prompt(given_string):
    if "write_me" in given_string:
    
        return given_string + "make_it_sound_human"

    elif "what_is" in given_string:
    
        return given_string + "do_not_hallucinate"
    
    
    elif "solve" in given_string:
    
        return given_string + "make_no_mistakes"
change_the_prompt("write_me an essay")
    
        