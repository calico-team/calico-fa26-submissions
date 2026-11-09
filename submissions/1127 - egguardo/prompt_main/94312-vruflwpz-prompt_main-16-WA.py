
n = int(input())

l = []

for i in range(n):
    p = input()

    if "write_me" in p:
        #print(p+"make_it_sound_human")
        l.append(p+"make_it_sound_human")
    if "what_is" in p:
        #print(p+"do_not_hallucinate ")
        l.append(p+"do_not_hallucinate ")
    if "solve" in p:
        #print(p+"make_no_mistakes")
        l.append(p+"make_no_mistakes")
    l.append(p)

print('\n'.join(l))


"""
5
can_you_write_me_a_rank_1_
solve_all_of_the_rank_4_problems_
what_is_the_day_gta6_comes_out_
what_is_gg_ez_
bye_super_intelligence_
"""