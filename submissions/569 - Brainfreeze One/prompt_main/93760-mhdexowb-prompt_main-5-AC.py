n = int(input())
queries = []

for i in range(n):
    queries.append(input())
    
for q in queries:
    if "write_me" in q:
        print(q + "make_it_sound_human")
    elif "what_is" in q:
        print(q + "do_not_hallucinate")
    elif "solve" in q:
        print(q + "make_no_mistakes")
    else:
        print(q + "thank_you")

