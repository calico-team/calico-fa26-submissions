def solve(S: str) -> str:
	s = S.strip()
	if "write_me" in s:
		return s+ "make_it_sound_human"
	elif "what_is" in s:
		return s+ "do_not_hallucinate"
	elif "solve" in s:
		return s+ "make_no_mistakes"
	else:
		return s+ "thank_you"
def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()