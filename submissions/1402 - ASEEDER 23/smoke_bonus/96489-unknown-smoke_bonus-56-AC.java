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
			long rechargeDuration = Long.parseLong(scanner.next());
			long[] rechargeTimes = new long[2];
			int pendingRecharges = 0;
			boolean possible = true;

			for (int i = 0; i < n; i++) {
				long time = Long.parseLong(scanner.next());
				if (!possible) {
					continue;
				}

				while (pendingRecharges > 0 && rechargeTimes[0] <= time) {
					if (pendingRecharges == 2) {
						rechargeTimes[0] = rechargeTimes[1];
					}
					pendingRecharges--;
				}

				if (pendingRecharges == 2) {
					possible = false;
				} else if (pendingRecharges == 0) {
					rechargeTimes[0] = time + rechargeDuration;
					pendingRecharges = 1;
				} else {
					rechargeTimes[1] = rechargeTimes[0] + rechargeDuration;
					pendingRecharges = 2;
				}
			}
			output.println(possible ? "YES" : "NO");
		}
		output.flush();
	}
}
