import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
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

	private static int lowerBound(ArrayList<Integer> values, long target) {
		int low = 0;
		int high = values.size();
		while (low < high) {
			int middle = low + (high - low) / 2;
			if (values.get(middle) < target) {
				low = middle + 1;
			} else {
				high = middle;
			}
		}
		return low;
	}

	private static int upperBound(ArrayList<Integer> values, long target) {
		int low = 0;
		int high = values.size();
		while (low < high) {
			int middle = low + (high - low) / 2;
			if (values.get(middle) <= target) {
				low = middle + 1;
			} else {
				high = middle;
			}
		}
		return low;
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
			long nights = Long.parseLong(scanner.next());
			Map<Integer, ArrayList<Integer>> northByDiagonal = new HashMap<>();
			ArrayList<int[]> eastDrones = new ArrayList<>();

			for (int i = 0; i < n; i++) {
				int x = Integer.parseInt(scanner.next());
				int y = Integer.parseInt(scanner.next());
				scanner.next();
				String direction = scanner.next();
				int diagonal = x + y;

				if (direction.equals("N")) {
					northByDiagonal.computeIfAbsent(diagonal, key -> new ArrayList<>()).add(x);
				} else {
					eastDrones.add(new int[] {x, diagonal});
				}
			}

			for (ArrayList<Integer> northX : northByDiagonal.values()) {
				Collections.sort(northX);
			}

			long blockedRain = 0;
			for (int[] eastDrone : eastDrones) {
				ArrayList<Integer> northX = northByDiagonal.get(eastDrone[1]);
				if (northX == null) {
					continue;
				}

				long firstNorthX = eastDrone[0] + 1L;
				long lastNorthX = eastDrone[0] + nights - 1;
				if (firstNorthX <= lastNorthX) {
					blockedRain += upperBound(northX, lastNorthX) - lowerBound(northX, firstNorthX);
				}
			}

			output.println((long) n * nights - blockedRain);
		}
		output.flush();
	}
}
