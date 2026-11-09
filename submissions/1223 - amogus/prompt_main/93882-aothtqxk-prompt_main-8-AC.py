t = int(input())
lelistsigma = []
for i in range(t):
    s = input()
    if "write_me" in s:
        whattooutput = (s + "make_it_sound_human")
        lelistsigma.append(whattooutput)
    elif "what_is" in s:
        whattooutput = (s + "do_not_hallucinate") 
        lelistsigma.append(whattooutput)
    elif "solve" in s:
        whattooutput = (s + "make_no_mistakes")   
        lelistsigma.append(whattooutput) 
    else:
        whattooutput = (s + "thank_you") 
        lelistsigma.append(whattooutput)

for i in lelistsigma:
    print(i)
