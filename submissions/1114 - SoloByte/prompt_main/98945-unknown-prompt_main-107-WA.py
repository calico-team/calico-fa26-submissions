S = input("")

if "write_me" in S:
  S = "".join([S, 'make_it_sound_human'])
elif "what_is" in S:
  S = "".join([S, 'do_not_hallucinate'])
elif "solve" in S:
  S = "".join([S, 'make_no_mistakes'])
else:
  S = "".join([S, "thank_you"])

print(S)

