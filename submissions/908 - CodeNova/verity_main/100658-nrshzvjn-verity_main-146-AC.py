import sys


def main():
    inp = sys.stdin.buffer
    out = sys.stdout


    def read_line():
        while True:
            line = inp.readline()
            if not line:
                return b""
            line = line.strip()
            if line:
                return line

    first = read_line()
    if not first:
        return

    t = int(first)

    for _ in range(t):
        line = read_line().split()
        while len(line) < 2:
            line += read_line().split()

        n = int(line[0])
        k = int(line[1])

        tokens = read_line().split()
        letters = []
        for token in tokens:
            if len(token) == 1:
                letters.append(token.decode())

            else:
                letters.extend(chr(b) for b in token)

        while len(letters) < k:
            for token in read_line().split():
                if len(token) == 1:
                    letters.append(token.decode())
                else:
                    letters.extend(chr(b) for b in token)

        letters = letters[:k]

        answer = ["?"] * n
        solved = False
        

        for c in letters:
            out.write(c * n + "\n")
            out.flush()

            reply = read_line().decode()

            if reply =="CORRECT":
                solved = True
                break

            for i in range(min(n, len(reply))):
                if reply[i] != "_":
                    answer[i] = reply[i]

        if not solved:
            out.write("".join(answer) + "\n")
            out.flush()
            read_line()


if __name__ == "__main__":
    main()