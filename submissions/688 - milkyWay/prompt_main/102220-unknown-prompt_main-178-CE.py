def solve(S: str) -> str:
	"""
	Output the result of adding a certain string to the end of a prompt.

	S: Original prompt
	"""
    if "write_me" in S:
        suffix = "make_it_sound_human"
    elif "what_is" in S:
        suffix = "do_not_hallucinate"
    elif "solve" in S:
        suffix = "make_no_mistakes"
    else:
        suffix = "thank_you" # no pattern identifed

    return S + suffix # attach suffix directly

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()