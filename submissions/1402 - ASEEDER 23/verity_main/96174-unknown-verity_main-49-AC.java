import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
	private static final class FastScanner {
		private final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		private StringTokenizer tokenizer;

		String next() throws IOException {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				String line = reader.readLine();
				if (line == null) {
					return null;
				}
				tokenizer = new StringTokenizer(line);
			}
			return tokenizer.nextToken();
		}
	}

	public static void main(String[] args) throws IOException {
		FastScanner scanner = new FastScanner();
		PrintWriter output = new PrintWriter(System.out);
		String firstToken = scanner.next();
		if (firstToken == null) {
			return;
		}

		int testCases = Integer.parseInt(firstToken);
		for (int testCase = 0; testCase < testCases; testCase++) {
			int n = Integer.parseInt(scanner.next());
			int k = Integer.parseInt(scanner.next());
			char[] alphabet = new char[k];
			for (int i = 0; i < k; i++) {
				alphabet[i] = scanner.next().charAt(0);
			}

			char[] known = new char[n];
			boolean solved = false;
			for (char candidate : alphabet) {
				StringBuilder guess = new StringBuilder(n);
				for (int i = 0; i < n; i++) {
					guess.append(known[i] == 0 ? candidate : known[i]);
				}

				output.println(guess);
				output.flush();

				String response = scanner.next();
				if (response == null) {
					return;
				}
				if (response.equals("CORRECT")) {
					solved = true;
					break;
				}

				for (int i = 0; i < n; i++) {
					if (response.charAt(i) != '_') {
						known[i] = response.charAt(i);
					}
				}
			}

			if (!solved) {
				return;
			}
		}
	}
}
