import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	private static final int[] ROW_DELTA = {-1, 1, 0, 0};
	private static final int[] COLUMN_DELTA = {0, 0, -1, 1};

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

	private static boolean isActive(char tile, int mode) {
		return tile == '.' || (tile == 'B' && mode == 0) || (tile == 'R' && mode == 1);
	}

	private static int[] findComponents(char[][] grid, int rows, int columns) {
		int stateCount = rows * columns * 2;
		int[] component = new int[stateCount];
		Arrays.fill(component, -1);
		int[] queue = new int[stateCount];
		int componentId = 0;

		for (int start = 0; start < stateCount; start++) {
			int startCell = start / 2;
			int startMode = start % 2;
			if (component[start] != -1 || !isActive(grid[startCell / columns][startCell % columns], startMode)) {
				continue;
			}

			int head = 0;
			int tail = 0;
			queue[tail++] = start;
			component[start] = componentId;

			while (head < tail) {
				int state = queue[head++];
				int cell = state / 2;
				int mode = state % 2;
				int row = cell / columns;
				int column = cell % columns;

				for (int direction = 0; direction < 4; direction++) {
					int nextRow = row + ROW_DELTA[direction];
					int nextColumn = column + COLUMN_DELTA[direction];
					if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns
							|| !isActive(grid[nextRow][nextColumn], mode)) {
						continue;
					}

					int nextState = (nextRow * columns + nextColumn) * 2 + mode;
					if (component[nextState] == -1) {
						component[nextState] = componentId;
						queue[tail++] = nextState;
					}
				}

				if (grid[row][column] == '.') {
					int nextState = state ^ 1;
					if (component[nextState] == -1) {
						component[nextState] = componentId;
						queue[tail++] = nextState;
					}
				}
			}

			componentId++;
		}

		return component;
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
			int rows = Integer.parseInt(scanner.next());
			int columns = Integer.parseInt(scanner.next());
			int queryCount = Integer.parseInt(scanner.next());
			char[][] grid = new char[rows][columns];
			for (int row = 0; row < rows; row++) {
				grid[row] = scanner.next().toCharArray();
			}

			int[] component = findComponents(grid, rows, columns);
			for (int query = 0; query < queryCount; query++) {
				int startRow = Integer.parseInt(scanner.next());
				int startColumn = Integer.parseInt(scanner.next());
				int endRow = Integer.parseInt(scanner.next());
				int endColumn = Integer.parseInt(scanner.next());

				int startState = (startRow * columns + startColumn) * 2;
				int endCellState = (endRow * columns + endColumn) * 2;
				int startComponent = component[startState];
				boolean reachable = isActive(grid[endRow][endColumn], 0)
						&& component[endCellState] == startComponent;
				if (!reachable && isActive(grid[endRow][endColumn], 1)) {
					reachable = component[endCellState + 1] == startComponent;
				}

				output.println(reachable ? "YES" : "NO");
			}
		}
		output.flush();
	}
}
