import sys


def main():
  # Read all lines from standard input efficiently
  input_data = sys.stdin.read().splitlines()
  if not input_data:
    return

  # The first line is the number of test cases T
  T = int(input_data[0])

  # Process each test case string S
  for i in range(1, T + 1):
    s = input_data[i]

    # Check for the presence of each substring and append the correct suffix
    if "write_me" in s:
      print(s + "make_it_sound_human")
    elif "what_is" in s:
      print(s + "do_not_hallucinate")
    elif "solve" in s:
      print(s + "make_no_mistakes")
    else:
      print(s + "thank_you")


if __name__ == "__main__":
  main()