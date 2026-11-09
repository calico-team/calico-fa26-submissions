def solve(S: str) -> str:
    if S == "write_me" :
        S += "make_it_sound_human"
        return solve(S)
    else:
        if S == what_is :
            S += "do_not_hallucinate"
            return solve(S)
        else:
            if S == "solve" :
                S+= "make_no_mistakes"
                return solve(S)
            else:
                S+= "thank_you"
                return solve(S)

def main():
	T = int(input())
	for _ in range(T):
		S = input()
		print(solve(S))

if __name__ == "__main__":
	main()