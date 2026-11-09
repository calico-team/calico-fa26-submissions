T = int(input())
for i in range(T):
  prompt =input().lower()
  prompt = "_".join(prompt.split())

  if "write_me" in prompt:
    prompt = prompt + "make_it_sound_human"
  elif "do_not" in prompt:
    prompt = prompt + "do_not_hallucinate"
  elif "solve" in prompt:
    prompt = prompt + "make_no_mistakes"
  else: 
    prompt = prompt + "thank_you"
  print(prompt)