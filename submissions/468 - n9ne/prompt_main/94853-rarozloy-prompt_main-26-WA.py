def solve(S: str) -> str:
	S=str(S)
	if "write_to_me" in S:
		return S+"make_it_sound_human"
	elif "what_is" in S:
		return S+"do_not_hallucinate"
	elif "solve" in S:
		return S+"make_no_mistakes"	
	return S+"thank_you"

def main():
	T = int(input())
	for _ in range(T):
		S = str(input())
		print(solve(str(S)))

if __name__ == "__main__":
	main()