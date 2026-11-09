public class calico_2026_2 {
    public static void main (String[] args) throws Exception {
        int b = System.in.read();
        while (b <= 32) {
            if (b == -1) {
                return;
            }
            b = System.in.read();
        }
        int t = 0;
        while (b > 32) {
            t = t * 10 + (b - '0');
            b = System.in.read();
        }
        for (int i = 0; i < t; i++) {
            while (b <= 32 && b != -1) {
                b = System.in.read();
            }
            int n = 0;
            while (b > 32) {
                n = n * 10 + (b - '0');
                b = System.in.read();
            }

            while (b <= 32 && b != -1) {
                b = System.in.read();
            }
            int m = 0;
            while (b > 32) {
                m = m * 10 + (b - '0');
                b = System.in.read();
            }

            while (b <= 32 && b != -1) {
                b = System.in.read();
            }
            int q = 0;
            while (b > 32) {
                q = q * 10 + (b - '0');
                System.in.read();
            }

            int [][] grid = new int [n][m];

            for (int eq = 0; eq < q; eq++) {
                while (b <= 32 && b != -1) {
                    b = System.in.read();
                }
                int row = 0;
                while (b > 32) {
                    row = row * 10 + (b - '0');
                    b = System.in.read();
                }

                while (b <= 32 && b != -1) {
                    b = System.in.read();
                }
                int col = 0;
                while (b > 32) {
                    col = col * 10 + (b - '0');
                    b = System.in.read();
                }

                while (b <= 32 && b != -1) {
                    b = System.in.read();
                }
                long valp = 0;
                while (b > 32) {
                    valp = valp * 10 + (b - '0');
                    b = System.in.read();
                }
                long pSq = valp * valp;

                int startR = (int) Math.max(0, row - valp);
                int endR = (int) Math.min(n-1, row + valp);
                int startC = (int) Math.max(0, col-valp);
                int endC = (int) Math.min(m-1, col + valp);

                for (int r = startR; r <= endR; r++) {
                    long dr = r - row;
                    long drSq = dr * dr;
                    for (int c = startC; c <= endC; c++) {
                        long dc = c - col;
                        long distSq = drSq + dc * dc;

                        long shock = pSq - distSq + 1;
                        if (shock > 0) {
                            grid[r][c] = (int) shock;
                        }
                    }
                }

            }
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    System.out.print(grid[r][c]);
                    if (c < m - 1) {
                        System.out.print(" ");
                    }
                }
                System.out.println();
            }
        }
    }
}
