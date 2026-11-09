t = int(input())
answers = []
updated = ""

for i in range (0, t):
  text = input()
  updated = ""
  if "write_me" in text:
    updated = text + "make_it_sound_human"
    answers.append(updated)
  elif "what_is" in text:
    updated = text + "do_not_hallucinate"
    answers.append(updated)
  elif "solve" in text:
    updated = text + "make_no_mistakes"
    answers.append(updated)
  else:
    updated = text + "thank_you"
    answers.append(updated)

for i in range(0, t):
  print(answers[i])