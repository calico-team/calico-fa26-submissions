import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class three {
    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        
        if (!sc.hasNext()) return;
        int T = sc.nextInt();

        while (T-- > 0) {
            int N = sc.nextInt();
            int K = sc.nextInt();

            char[] A = new char[K];
            for (int i = 0; i < K; i++) {
                A[i] = sc.next().charAt(0);
            }

            char[] ans = new char[N];
            for (int i = 0; i < N; i++) ans[i] = '_';

            for (int k = 0; k < K; k++) {
                char c = A[k];

                StringBuilder guess = new StringBuilder();
                for (int i = 0; i < N; i++) {
                    if (ans[i] != '_') {
                        guess.append(ans[i]);
                    } else {
                        guess.append(c);
                    }
                }

                // Output guess and flush output stream for interactive judging
                System.out.println(guess.toString());
                System.out.flush();

                String response = sc.next();

                if (response.equals("CORRECT")) {
                    break;
                }

                for (int i = 0; i < N; i++) {
                    if (response.charAt(i) != '_') {
                        ans[i] = response.charAt(i);
                    }
                }
            }
        }
    }

    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        boolean hasNext() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    String line = br.readLine();
                    if (line == null) return false;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    return false;
                }
            }
            return true;
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}