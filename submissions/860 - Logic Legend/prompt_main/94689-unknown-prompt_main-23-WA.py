# Source: https://usaco.guide/general
import sys

def solve(s):
    if "write_me" in s: return s + "_processed"
    if "what_is" in s: return s + "_verified"
    if "solve" in s: return s + "_resolved"
    return s + "_ok"

def main():
    lines = [line.strip() for line in sys.stdin if line.strip()]
    if not lines:
        return
    
    t = int(lines[0])
    for s in lines[1:t+1]:
        print(solve(s))

if __name__ == "__main__":
    main()
