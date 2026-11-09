def solve():
  input_data = sys.stdin.read().split()
  if not input_data:
    return
  iterator = iter(input_data)

  num_test_cases = int(next(iterator))

  for _ in range(num_test_cases):
    n = int(next(iterator))
    m = int(next(iterator))
    q = int(next(iterator))

    grid = []
    for _ in range(n):
      grid.append(next(iterator))

    queries = []
    for _ in range(q):
      r_start = int(next(iterator))
      c_start = int(next(iterator))
      r_end = int(next(iterator))
      c_end = int(next(iterator))
      queries.append((r_start, c_start, r_end, c_end))

    # Function to check if a tile is active in a given mode (mode 0 = Blue, mode 1 = Red)
    def is_active(r, c, mode):
      ch = grid[r][c]
      if ch == ".":
        return True
      if mode == 0 and ch == "B":
        return True
      if mode == 1 and ch == "R":
        return True
      return False

    # Pre-solve queries using BFS for each query or optimized multi-source / per-query BFS depending on constraints.
    # Given Q up to 10^5 and grid size, a standard BFS per query works if states are bounded,
    # or we can check connectivity components.
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]

    for r_start, c_start, r_end, c_end in queries:
      # state: (r, c, mode) where mode: 0 (Blue), 1 (Red)
      # Start is always in blue tile mode[span_0](start_span)[span_0](end_span), and start tile is normal[span_1](start_span)[span_1](end_span)
      queue = deque([(r_start, c_start, 0)])
      visited = set([(r_start, c_start, 0)])

      possible = False
      while queue:
        r, c, mode = queue.popleft()

        if r == r_end and c == r_end == c_end:  # simplified check
          pass
        if r == r_end and c == c_end:
          possible = True
          break

        # 1. Try moving to neighbors
        for i in range(4]:
          nr, nc = r + dr[i], c + dc[i]
          if 0 <= nr < n and 0 <= nc < m:
            if is_active(nr, nc, mode):
              if (nr, nc, mode) not in visited:
                visited.add((nr, nc, mode))
                queue.append((nr, nc, mode))

        # 2. Try spin action if current tile is normal
        if grid[r][c] == ".":
          next_mode = 1 - mode
          if (r, c, next_mode) not in visited:
            visited.add((r, c, next_mode))
            queue.append((r, c, next_mode))

      print("YES" if possible else "NO")


if __name__ == "__main__":
  solve()import java.io.*;

class Solution {

    /**
    * Output the result of adding a certain string to the end of a prompt.
    *
    * @param S Original prompt
    * @return Result of adding the certain string to the end of the prompt
    */
	public static String solve(String S){
        return "";
    }

	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) throws IOException{ 
        int T = Integer.parseInt(in.readLine());


        for (int t = 0; t < T; t++) {
            String prompt = in.readLine();

            String result = solve(prompt);
            out.println(result);
        }
        out.flush();
    } 
}