def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	x=S
	if "write_me" in S:
		x=x.replace("write_me", "make_it_sound_human ")
	elif "what_is" in S:
		x=x.replace("what_is", "do_not_hallucinate ")
	elif "solve" in S:
		x=x.replace("solve","make_no_mistakes")
	else:
		x += "thank_you"
	


	return x


def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()