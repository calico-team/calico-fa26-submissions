sample_input = input("input:")
check1 = "write_me"
check2 = "what_is"
check3 = "solve"
times = len(sample_input)
checkpoint1 = 0
checkpoint2 = 0
checkpoint3 = 0

i = 0

while i < times:
    if sample_input[i] == "w":
        if times - i > 6:
            i2 = 0
            while i2 < 7:
                if sample_input[i2 + i] == check1[i2]:
                    checkpoint1 = checkpoint1 + 1
                i2 = i2 + 1
    i = i + 1

i = 0

while i < times:
    if sample_input[i] == "w":
        if times - i > 5:
            i2 = 0
            while i2 < 6:
                if sample_input[i2 + i] == check2[i2]:
                    checkpoint2 = checkpoint2 + 1
                i2 = i2 + 1
    i = i + 1

i = 0

while i < times:
    if sample_input[i] == "s":
        if times - i > 3:
            i2 = 0
            while i2 < 4:
                if sample_input[i2 + i] == check3[i2]:
                    checkpoint3 = checkpoint3 + 1
                i2 = i2 + 1
    i = i + 1

if checkpoint3 == 4:
    print(sample_input,"make_no_mistakes",sep = '')
elif checkpoint2 == 6:
    print(sample_input,"do_not_hallucinate",sep = '')
elif checkpoint1 == 7:
    print(sample_input,"make_it_sound_human",sep = '')
else:
    print(sample_input,"thank_you",sep = '')
