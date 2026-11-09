import random

alp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
do_times = 0
have_do_times = int(input("time:"))
while do_times < have_do_times:
    check = 0
    while check != "CORRECT":
        long = int(input("long:"))
        number = random.randint(0,47)
        print(alp[number])
    do_times = do_times + 1
