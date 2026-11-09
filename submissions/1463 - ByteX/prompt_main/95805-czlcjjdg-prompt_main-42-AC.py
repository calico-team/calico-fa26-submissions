def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""

	## If the prompt has "write_me" anywhere inside it,
	## stick "make_it_sound_human" on the end and hand it back.
	if "write_me" in S:
		return S + "make_it_sound_human"
	
	## Otherwise, if it has "what_is" anywhere inside it,
	## stick "do_not_hallucinate" on the end.
	if "what_is" in S:
		return S + "do_not_hallucinate"
	
	## Otherwise, if it has "solve" anywhere inside it,
	## stick "make_no_mistakes" on the end.
	if "solve" in S:
		return S + "make_no_mistakes"
	
	## If none of the three words showed up,
	## just stick "thank_you" on the end.
	return S + "thank_you" 

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()