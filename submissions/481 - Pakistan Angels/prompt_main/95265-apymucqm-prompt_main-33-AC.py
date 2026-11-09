def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	final_prompt = S
	if "write_me" in S:
		final_prompt +="make_it_sound_human"
	elif "what_is" in S:
		final_prompt+="do_not_hallucinate"
	elif "solve" in S:
		final_prompt+="make_no_mistakes"
	else:
		final_prompt+="thank_you"	
	return final_prompt

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()