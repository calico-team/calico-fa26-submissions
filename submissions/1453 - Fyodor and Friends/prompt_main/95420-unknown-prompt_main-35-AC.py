def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
	end = S
	if "write_me" in S:
		end += "make_it_sound_human"
	elif "what_is" in S:
		end += "do_not_hallucinate"
	elif "solve" in S:
		end += "make_no_mistakes"
	else:
		end += "thank_you"
	return end

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()