
import java.util.Scanner;

class answer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        for (int i = 0; i < t; i++) {
            int n = sc.nextInt();
            int k = sc.nextInt();

            char[] letters = new char[k];
            for (int j = 0; j < k; j++) {
                letters[j] = sc.next().charAt(0);
            }

            char[] guess = new char[n];
            boolean[] found = new boolean[n];

            for (int j = 0; j < k; j++) {
                for (int x = 0; x < n; x++) {
                    if (!found[x]) {
                        guess[x] = letters[j];
                    }
                }

                System.out.println(new String(guess));
                System.out.flush();

                String response = sc.next();

                if (response.equals("CORRECT")) {
                    break;
                }

                for (int x = 0; x < n; x++) {
                    if (response.charAt(x) != '_') {
                        found[x] = true;
                    }
                }
            }
        }

        sc.close();
    }
}
