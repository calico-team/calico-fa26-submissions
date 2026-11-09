m = int(input("Enter the number of string you want to enter:"))  

for _ in range(m):
    n = input("Enter the string:")   

    if "write_me" in n:
        print(n + "make_it_sound_human")
    elif "what_is" in n:
        print(n + "do_not_hallucinate")
    elif "solve" in n:
        print(n + "make_no_mistakes")
    else:
        print(n+ "thank_you")
