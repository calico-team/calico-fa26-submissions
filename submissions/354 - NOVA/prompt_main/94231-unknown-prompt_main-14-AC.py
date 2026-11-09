a = int(input())

lst = []
for j in range(a):
   c = input()
   lst.append(c)


for i in range(a):
    b = lst[i]
    
    
    if "write_me" in b:
        print(b + "make_it_sound_human")
    
    elif "what_is" in b:
        print(b + "do_not_hallucinate")
        
    elif "solve" in b:
        print(b + "make_no_mistakes")
    
    else:
        print(b + "thank_you")
        