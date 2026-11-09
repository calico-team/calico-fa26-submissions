data = """5
can_you_write_me_a_rank_1_
solve_all_of_the_rank_4_problems_
what_is_the_day_gta6_comes_out_
what_is_gg_ez_
bye_super_intelligence_"""

lines = data.strip().split('\n')

t = int(lines[0])

for s in lines[1:t+1]:
    if "write_me" in s:
        print(s + "make_it_sound_human")
    elif "what_is" in s:
        print(s + "do_not_hallucinate")
    elif "solve" in s:
        print(s + "make_no_mistakes")
    else:
        print(s + "thank_you")
