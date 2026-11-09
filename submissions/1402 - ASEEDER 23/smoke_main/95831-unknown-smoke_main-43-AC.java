import java.io.BufferedInputStream;
import java.io.IOException;

public class Main {
	private static final class FastScanner {
		private final BufferedInputStream input = new BufferedInputStream(System.in);
		private final byte[] buffer = new byte[1 << 16];
		private int length;
		private int pointer;

		private int read() throws IOException {
			if (pointer >= length) {
				length = input.read(buffer);
				pointer = 0;
				if (length == -1) {
					return -1;
				}
			}
			return buffer[pointer++];
		}

		long nextLong() throws IOException {
			int character;
			do {
				character = read();
			} while (character <= ' ' && character != -1);

			long value = 0;
			while (character > ' ') {
				value = value * 10 + character - '0';
				character = read();
			}
			return value;
		}
	}

	public static void main(String[] args) throws IOException {
		FastScanner scanner = new FastScanner();
		int testCases = (int) scanner.nextLong();
		StringBuilder output = new StringBuilder();

		for (int testCase = 0; testCase < testCases; testCase++) {
			int requestCount = (int) scanner.nextLong();
			long rechargeDuration = scanner.nextLong();
			long[] rechargeTimes = new long[2];
			int pendingRecharges = 0;
			boolean possible = true;

			for (int i = 0; i < requestCount; i++) {
				long time = scanner.nextLong();
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

			output.append(possible ? "YES" : "NO").append('\n');
		}

		System.out.print(output);
	}
}
