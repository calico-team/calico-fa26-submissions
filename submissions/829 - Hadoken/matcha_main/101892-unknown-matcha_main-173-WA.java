import java.io.InputStream;
import java.io.IOException;

public class Main {
    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[32768];
        private int patr = 0;
        private int len = 0;

        private int read() {
            if (patr >= len) {
                patr = 0;
                try {
                    len = in.read(buffer, 0, buffer.length);
                } catch (IOException e) {
                    return -1;
                }
                if (len <= 0) return -1;
            }
            return buffer[patr++];
        }

        public int nextInt() {
            int ch = read();
            while (ch <= 32) {
                if (ch == -1) return -1;
                ch = read();
            }
            int result = 0;
            while (ch > 32) {
                if (ch < '0' || ch > '9') break;
                result = result * 10 + ch - '0';
                ch = read();
            }
            return result;
        }

        public long nextLong() {
            int ch = read();
            while (ch <= 32) {
                if (ch == -1) return -1;
                ch = read();
            }
            long result = 0;
            while (ch > 32) {
                if (ch < '0' || ch > '9') break;
                result = result * 10 + ch - '0';
                ch = read();
            }
            return result;
        }
    }

    static class FlexState {
        int type;
        long limit;

        FlexState(int type, long limit) {
            this.type = type;
            this.limit = limit;
        }
    }

    static final FlexState STATE_NONE = new FlexState(0, 0);

    static int[] fixedCount = new int[30];
    static int[] generalCount = new int[30];
    static long[] generalL = new long[30];
    static long[] generalR = new long[30];

    public static void main(String[] args) {
        FastScanner scanner = new FastScanner();
        int testCases = scanner.nextInt();
        if (testCases == -1) return;
        StringBuilder out = new StringBuilder();

        while (testCases-- > 0) {
            int n = scanner.nextInt();
            long[] leftBounds = new long[n];
            long[] rightBounds = new long[n];

            for (int i = 0; i < n; i++) {
                leftBounds[i] = scanner.nextLong();
            }
            for (int i = 0; i < n; i++) {
                rightBounds[i] = scanner.nextLong();
            }

            for (int bit = 0; bit < 30; bit++) {
                fixedCount[bit] = 0;
                generalCount[bit] = 0;
            }

            for (int i = 0; i < n; i++) {
                long left = leftBounds[i];
                long right = rightBounds[i];

                if (left == right) {
                    for (int bit = 0; bit < 30; bit++) {
                        if (((left >> bit) & 1) == 1) {
                            fixedCount[bit]++;
                        }
                    }
                } else {
                    long xorVal = left ^ right;
                    int msb = 63 - Long.numberOfLeadingZeros(xorVal);
                    generalCount[msb]++;
                    generalL[msb] = left;
                    generalR[msb] = right;
                    
                    for (int bit = msb + 1; bit < 30; bit++) {
                        if (((left >> bit) & 1) == 1) {
                            fixedCount[bit]++;
                        }
                    }
                }
            }

            long answer = solve(29, STATE_NONE);
            out.append(answer).append("\n");
        }

        System.out.print(out);
    }

    static long solve(int bit, FlexState state) {
        if (bit < 0) return 0;

        long mask = 1L << bit;
        boolean existingIsFlex = false;
        long existingFixedBit = 0;
        long nextVal = 0;

        if (state.type == 1) { 
            long left = state.limit;
            if (left >= mask) {
                existingIsFlex = false;
                existingFixedBit = 1;
                nextVal = left - mask;
            } else {
                existingIsFlex = true;
            }
        } else if (state.type == 2) {
            long right = state.limit;
            if (right < mask) {
                existingIsFlex = false;
                existingFixedBit = 0;
                nextVal = right;
            } else {
                existingIsFlex = true;
            }
        }
        int totalFlexible = (existingIsFlex ? 1 : 0) + generalCount[bit];
        long fixedXor = (fixedCount[bit] % 2) ^ (existingIsFlex ? 0 : existingFixedBit);
        if (totalFlexible >= 2) {
            return (1L << (bit + 1)) - 1;
        }
        if (totalFlexible == 0) {
            FlexState nextState = STATE_NONE;
            if (state.type == 1 && state.limit >= mask) {
                nextState = new FlexState(1, nextVal);
            } else if (state.type == 2 && state.limit < mask) {
                nextState = new FlexState(2, nextVal);
            }
            return (fixedXor << bit) + solve(bit - 1, nextState);
        }
        if (existingIsFlex) {
            if (state.type == 1) {
                long left = state.limit;
                long option0 = (fixedXor << bit) + solve(bit - 1, new FlexState(1, left));
                long option1 = ((fixedXor ^ 1) << bit) + (1L << bit) - 1;
                return Math.max(option0, option1);
            } else { 
                long right = state.limit;
                long option0 = (fixedXor << bit) + (1L << bit) - 1;
                long option1 = ((fixedXor ^ 1) << bit) + solve(bit - 1, new FlexState(2, right - mask));
                return Math.max(option0, option1);
            }
        } else {
            long left = generalL[bit] & (mask - 1);
            long right = generalR[bit] & (mask - 1);

            long option0 = (fixedXor << bit) + solve(bit - 1, new FlexState(1, left));
            long option1 = ((fixedXor ^ 1) << bit) + solve(bit - 1, new FlexState(2, right));
            return Math.max(option0, option1);
        }
    }
}