ghar = int(input("Enter the single integer value for ghar: "))
for rehan in range(ghar):
    saqib_s = input(" koi prompt enter kardo:")
    if "write_me" in saqib_s:
        bech_ka_lafz = "make it sound human"
    elif "what_is" in saqib_s:
        bech_ka_lafz = "do not hallucinate"
    elif "solve" in saqib_s:
        bech_ka_lafz = "make no mistakes"
    else:
        "Thanks"
    print(saqib_s + " " + bech_ka_lafz)
    
