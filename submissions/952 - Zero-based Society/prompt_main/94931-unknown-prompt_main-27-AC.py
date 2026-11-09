def solve(S: str) -> str:
	if "write_me" in S:
		S+="make_it_sound_human"
	elif "what_is" in S:
		S+="do_not_hallucinate "
	elif "solve" in S:
		S+="make_no_mistakes"
	else:
		S+="thank_you"


	# """
	# Output the result of adding a certain string to the end of a prompt.

	# S: Original prompt
	# """
	return S

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()