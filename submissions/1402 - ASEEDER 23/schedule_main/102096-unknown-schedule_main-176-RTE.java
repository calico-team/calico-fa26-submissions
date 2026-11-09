import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {
	static class FastScanner {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokens;

		String next() throws IOException {
			while (tokens == null || !tokens.hasMoreTokens()) {
				tokens = new StringTokenizer(reader.readLine());
			}
			return tokens.nextToken();
		}
	}

	public static void main(String[] args) throws IOException {
		FastScanner in = new FastScanner();
		PrintWriter out = new PrintWriter(System.out);
		String phase = read_your_input(in);
		int n = Integer.parseInt(read_your_input(in));

		if (phase.equals("FIRST")) {
			ArrayList<Integer>[] graph = new ArrayList[n + 1];
			for (int i = 1; i <= n; i++) graph[i] = new ArrayList<>();
			int[] degree = new int[n + 1];

			for (int i = 0; i < n - 1; i++) {
				int a = Integer.parseInt(read_your_input(in));
				int b = Integer.parseInt(read_your_input(in));
				graph[a].add(b);
				graph[b].add(a);
				degree[a]++;
				degree[b]++;
			}

			PriorityQueue<Integer> leaves = new PriorityQueue<>();
			for (int i = 1; i <= n; i++) if (degree[i] == 1) leaves.add(i);
			int[] code = new int[Math.max(0, n - 2)];
			for (int i = 0; i < code.length; i++) {
				int leaf = leaves.remove();
				for (int neighbor : graph[leaf]) {
					if (degree[neighbor] > 0) {
						code[i] = neighbor - 1;
						degree[neighbor]--;
						if (degree[neighbor] == 1) leaves.add(neighbor);
						break;
					}
				}
				degree[leaf] = 0;
			}

			int[] values = new int[n];
			long sum = 0;
			for (int i = 0; i < code.length; i++) {
				values[i] = code[i];
				sum += code[i];
			}
			if (n == 1) values[0] = 0;
			else {
				values[n - 2] = (int) (sum % n);
				values[n - 1] = 0;
			}

			for (int value : values) out.print(value + " ");
			out.println();
		} else {
			int[] values = new int[n];
			for (int i = 0; i < n; i++) values[i] = Integer.parseInt(read_your_input(in));

			long sum = 0;
			int missing = -1;
			for (int i = 0; i < n - 2; i++) {
				if (values[i] == -1) missing = i;
				else sum += values[i];
			}
			if (missing != -1) {
				values[missing] = (int) ((values[n - 2] - sum % n + n) % n);
			}

			int[] degree = new int[n + 1];
			Arrays.fill(degree, 1);
			for (int i = 0; i < n - 2; i++) degree[values[i] + 1]++;
			PriorityQueue<Integer> leaves = new PriorityQueue<>();
			for (int i = 1; i <= n; i++) if (degree[i] == 1) leaves.add(i);

			for (int i = 0; i < n - 2; i++) {
				int leaf = leaves.remove();
				int neighbor = values[i] + 1;
				out.println(leaf + " " + neighbor);
				degree[leaf]--;
				if (--degree[neighbor] == 1) leaves.add(neighbor);
			}
			if (n > 1) out.println(leaves.remove() + " " + leaves.remove());
		}
		out.flush();
	}

	static String read_your_input(FastScanner in) throws IOException {
		return in.next();
	}
}
