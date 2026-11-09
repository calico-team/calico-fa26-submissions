cases = int(input())

for _ in range(cases):
    word = input().strip()
    
    if "write_me" in word:
        print(word + "make_it_sound_human")
    elif "what_is" in word:
        print(word + "do_not_hallucinate")
    elif "solve" in word:
        print(word + "make_no_mistakes")
    else:
        print(word + "thank_you")
