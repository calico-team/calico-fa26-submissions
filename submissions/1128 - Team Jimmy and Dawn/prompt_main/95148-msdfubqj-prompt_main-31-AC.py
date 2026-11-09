
 
def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	if "write_me" in S:
		S = S + "make_it_sound_human"
		print(S)
	elif "what_is" in S:
		S = S + "do_not_hallucinate"
		print(S)
	elif "solve" in S:
		S = S + "make_no_mistakes"
		print(S)
	else:
		S = S + "thank_you"
		print(S)
		
	return ""

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()