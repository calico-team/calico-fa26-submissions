def solve(S: str) -> str:
    if "write_me" in inp:
        return (inp + "make_it_sound_human")
    elif "what_is" in inp:
        return (inp + "do_not_hallucinate")
    elif "solve" in inp:
        return (inp + "make_no_mistakes")
    else:
        return (inp + "thank_you")

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()