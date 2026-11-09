def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
    if "write_me" in s:
    s = s + "make_it_a_great_human":
    elif "what_if"in s:
        s = s + "do_not_hallucinate":
        elif "solve" in s:
            s = s + "make_no_mistakes":
            else:
                s = "thank_you":

                return s



def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()