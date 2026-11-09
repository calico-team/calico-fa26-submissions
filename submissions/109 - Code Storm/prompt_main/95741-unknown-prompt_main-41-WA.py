
list = ["write_me", "what_is", "solve"]
Test_cases_size = int(input("Enter the number of test cases: "))
for i in range(Test_cases_size):
    S = input("Enter the test case: ")

    if "write_me" in S:
        S += "make_it_sound_human"

    if "what_is" in S:
        S += "do_not_hallucinate"

    if "solve" in S:
        S += "make_no_mistakes"

    if "write_me" not in S and "what_is" not in S and "solve" not in S:
        S += "thank_you"

    print(S)

    