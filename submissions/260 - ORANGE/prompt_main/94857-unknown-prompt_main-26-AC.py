T=int(input(""))
for i in range (T):
   S=str(input(""))
   
   if "write_me" in S:
      print("{}make_it_sound_human".format(S))
   elif "what_is" in S:
      print("{}do_not_hallucinate".format(S))
   elif "solve" in S:
      print("{}make_no_mistakes".format(S))
   else:
      print("{}thank_you".format(S))