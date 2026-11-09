for _ in range(int(input())):
	T=input()
	if "write_me" in T:
		T+="make_it_sound_human"
	elif "what_is" in T:
		T+="do_not_hallucinate"
	elif "solve" in T:
		T+="make_no_mistakes"
	else:
		T+="thank_you"
	print(T)