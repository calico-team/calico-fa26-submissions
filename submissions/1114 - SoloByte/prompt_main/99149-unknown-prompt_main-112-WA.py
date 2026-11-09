S = input("")

if "write_me" in S:
  S = "".join([S, '_make_it_sound_human'])
elif "what_is" in S:
  S = "".join([S, '_do_not_hallucinate'])
elif "solve" in S:
  S = "".join([S, '_make_no_mistakes'])
else:
  S = "".join([S, "_thank_you"])

print(S)

