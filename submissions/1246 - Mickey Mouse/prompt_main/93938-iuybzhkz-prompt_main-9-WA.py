def solve(S: str):
    """
    Print one line for each token in S to draw the cookie.

    S: cookie name
    
    """
    word = [S]
    if "write_me" in S:
      word.append("make_it_sound_human")
    elif "what_is" in S:
      word.append("do_not_hallucinate")
    elif "solve" in S:
      word.append("make_no_mistakes") 
    else:
       word.append("thanks")
    print("".join(word))
                  
def main():
    T = int(input())
    for _ in range(T):
        S = input()
        solve(S)

if __name__ == '__main__':
    main()
