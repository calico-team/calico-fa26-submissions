def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""

	if "write_me" in S.lower():
		return S + "make_it_sound_human"
	elif "what_is" in S.lower():
		return S + "do_not_hallucinate"
	elif "solve" in S.lower(): 
		return S + "make_no_mistakes"
	return S + "thank_you"

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()