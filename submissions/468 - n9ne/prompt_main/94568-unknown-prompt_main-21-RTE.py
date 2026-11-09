def solve(S: str) -> str:
	if "write_to_me" in str:
		return S+"make_it_sound_human"
	elif "what_is" in str:
		return S+"do_not_hallucinate"
	elif "solve" in str:
		return S+"make_no_mistakes"	
	return S+"thank_you"

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()