T = int(input(''))
inp = []
ans = []
for i in range(T):
	inp.append(input(''))
for i in inp:
	if 'write_me' in i:
		ans.append(i + 'make_it_sound_human')
	elif 'what_is' in i:
		ans.append(i + 'do_not_hallucinate')
	elif 'solve' in i:
		ans.append(i + 'make_no_mistakes')
	else:
		ans.append(i + 'thank_you')
for a in ans:
	print(a)		
