n=int(input())
for i in range(n):
	tem=input()
	if ("write_me" in tem):
		print(tem+"make_it_sound_human")
	elif "what_is" in tem:
		print(tem+"do_not_hallucinate")
	elif "solve" in tem:
		print(tem+"make_no_mistakes")
	else:
		print(tem+"thank_you ")
