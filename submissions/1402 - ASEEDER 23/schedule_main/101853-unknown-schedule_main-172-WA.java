import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.PriorityQueue;
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
			int classCount = Integer.parseInt(scanner.next());
			long semesterLimit = Long.parseLong(scanner.next());
			long semesterCapacity = Long.parseLong(scanner.next());
			int[] prerequisite = new int[classCount + 1];
			int[] firstChild = new int[classCount + 1];
			int[] nextSibling = new int[classCount + 1];
			Arrays.fill(firstChild, -1);

			for (int course = 1; course <= classCount; course++) {
				int parent = Integer.parseInt(scanner.next());
				prerequisite[course] = parent;
				if (parent != 0) {
					nextSibling[course] = firstChild[parent];
					firstChild[parent] = course;
				}
			}

			int[] queue = new int[classCount];
			int head = 0;
			int tail = 0;
			for (int course = 1; course <= classCount; course++) {
				if (prerequisite[course] == 0) {
					queue[tail++] = course;
				}
			}
			while (head < tail) {
				int course = queue[head++];
				for (int child = firstChild[course]; child != -1; child = nextSibling[child]) {
					queue[tail++] = child;
				}
			}

			boolean possible = tail == classCount;
			if (possible) {
				int[] longestChain = new int[classCount + 1];
				for (int i = tail - 1; i >= 0; i--) {
					int course = queue[i];
					longestChain[course] = Math.max(longestChain[course], 1);
					int parent = prerequisite[course];
					if (parent != 0) {
						longestChain[parent] = Math.max(longestChain[parent], longestChain[course] + 1);
					}
				}

				PriorityQueue<Integer> available = new PriorityQueue<>((a, b) ->
						Integer.compare(longestChain[b], longestChain[a]));
				for (int course = 1; course <= classCount; course++) {
					if (prerequisite[course] == 0) {
						available.add(course);
					}
				}
				int completed = 0;
				long semester = 0;

				while (completed < classCount && semester <= semesterLimit && !available.isEmpty()) {
					int take = (int) Math.min(semesterCapacity, available.size());
					int[] selected = new int[take];
					for (int i = 0; i < take; i++) {
						selected[i] = available.remove();
					}
					completed += take;
					for (int course : selected) {
						for (int child = firstChild[course]; child != -1; child = nextSibling[child]) {
							available.add(child);
						}
					}
					semester++;
				}
				possible = completed == classCount;
			}

			output.println(possible ? "YES" : "NO");
		}
		output.flush();
	}
}
