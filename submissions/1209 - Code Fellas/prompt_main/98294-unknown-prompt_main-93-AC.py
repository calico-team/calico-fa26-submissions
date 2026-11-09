rey=int(input())
yan="make_it_sound_human"
bib="do_not_hallucinate"
ran="make_no_mistakes"
for kir in range(rey):
    hab=input()
    if "write_me" in hab:
        hab=hab+yan
    elif "what_is"in hab:
        hab=hab+bib
    elif "solve" in hab:
        hab=hab+ran 
    else:
        hab=hab+"Thank_you"
    print(hab)
