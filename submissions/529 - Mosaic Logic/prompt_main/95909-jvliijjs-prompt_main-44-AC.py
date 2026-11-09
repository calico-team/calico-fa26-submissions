tests = int(input())
for i in range(tests):
 prompt = input().strip()
 if "write_me" in prompt:
  print(prompt + "make_it_sound_human")
 elif "what_is" in prompt:
  print(prompt + "do_not_hallucinate")
 elif "solve" in prompt:
  print(prompt + "make_no_mistakes")
 else:
  print(prompt + "thank_you")
