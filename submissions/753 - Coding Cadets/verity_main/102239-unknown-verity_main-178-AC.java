import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);

        int t = sc.nextInt();

        while (t > 0) {
            t--;

            int n = sc.nextInt();
            int k = sc.nextInt();

            char[] chars = new char[k];
            for (int i = 0; i < k; i++) {
                chars[i] = sc.next().charAt(0);
            }

            char[] answer = new char[n];

            for (int c = 0; c < k; c++) {
                boolean allDone = true;
                for (int i = 0; i < n; i++) {
                    if (answer[i] == 0) {
                        allDone = false;
                        break;
                    }
                }
                if (allDone) break;

                String guess = "";
                for (int i = 0; i < n; i++) {
                    if (answer[i] != 0) {
                        guess = guess + answer[i];
                    } else {
                        guess = guess + chars[c];
                    }
                }

                out.println(guess);
                out.flush();

                String reply = sc.next();

                if (reply.equals("CORRECT")) {
                    break;
                }

                for (int i = 0; i < n; i++) {
                    if (reply.charAt(i) != '_') {
                        answer[i] = reply.charAt(i);
                    }
                }
            }

            boolean allDone = true;
            for (int i = 0; i < n; i++) {
                if (answer[i] == 0) {
                    allDone = false;
                    break;
                }
            }

            if (allDone) {
                String guess = "";
                for (int i = 0; i < n; i++) {
                    guess = guess + answer[i];
                }
                out.println(guess);
                out.flush();
                sc.next();
            }
        }

        out.close();
    }
}
