def solve(S: str) -> str:
	my_prompt = S
	if "write_me" in S:
		my_prompt +="make_it_sound_human"
	elif "what_is" in S:
		my_prompt+="do_not_hallucinate"
	elif "solve" in S:
		my_prompt+="make_no_mistakes"
	else:
		my_prompt+="thank_you"	
	return my_prompt

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()