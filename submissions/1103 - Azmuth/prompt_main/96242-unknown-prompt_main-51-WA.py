def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	if "write_me" in S:
		return S + "_make_it_sound_human"
	elif "what_is" in S:
		return S + "_do_not_hallucinate"
	elif "solve" in S:
		return S + "_make_no_mistakes"
	else:
		return S + "_thank_you"

	

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()