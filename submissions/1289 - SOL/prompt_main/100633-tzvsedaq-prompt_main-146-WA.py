t = int(input())


for i in range(t):
    s = input()
    if "write_me" in s:
        print (s+ "make it sound human")
    elif "what_is" in s:
        print (s+ "do_not_hallucinate")
    elif "solve" in s:
        print (s + "no mistakes")
    else:
        print (s+"thank you")