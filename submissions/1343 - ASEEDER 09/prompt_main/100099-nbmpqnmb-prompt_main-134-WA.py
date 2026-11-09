n =int(input(""))
s =input("")
for n in range(5):
    if n==8:
      print(str(s)+"thank_you")
      print(n)
    elif n==9:
      print(str(s)+"do_not_hallucinate")
      print(n)
    elif n ==6:
      print(str(s)+"make_no_mistakes")
      print(n)
    else:
      print(str(s)+"make_it_sound_human")
      print(n)
