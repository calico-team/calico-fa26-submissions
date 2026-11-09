n1 = int(input())
n2 = "make_it_sound_human"
n3 = "do_not_hallucinate"
n4 = "make_no_mistakes"
n5 = "thank_you"
n6 = []

for i in range(n1):
  n7 = input()
  if "write_me" in n7:
    n6.append(n7+n2)
  elif "what_is" in n7:
    n6.append(n7+n3)
  elif "solve" in n7:
    n6.append(n7+n4)
  else:
    n6.append(n7+n5)

for i in range(len(n6)):
  print(n6[i])