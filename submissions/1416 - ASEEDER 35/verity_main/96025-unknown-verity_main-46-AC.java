import java.util.Scanner;

public class verity {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;
        int T = sc.nextInt();

        while (T-- > 0) {
            int N = sc.nextInt();
            int K = sc.nextInt();
            
            String[] chars = new String[K];
            for (int i = 0; i < K; i++) {
                chars[i] = sc.next();
            }

            StringBuilder currentGuess = new StringBuilder();
            for (int i = 0; i < N; i++) {
                currentGuess.append("_");
            }

            int[] charIndex = new int[N]; 
            boolean isCorrect = false;

            while (!isCorrect) {
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < N; i++) {
                    if (currentGuess.charAt(i) == '_') {
                        sb.append(chars[charIndex[i]]);
                    } else {
                        
                        sb.append(currentGuess.charAt(i));
                    }
                }

                System.out.println(sb.toString());
                System.out.flush();

                  String response = sc.next();

            if (response.equals("CORRECT")) {
                    isCorrect = true; 
                } else {
                    
                    for (int i = 0; i < N; i++) {
                        if (response.charAt(i) != '_')                          
                           currentGuess.setCharAt(i, response.charAt(i));
                        else {
                            
                            charIndex[i]++;
                                if (charIndex[i] >= K) {
                                charIndex[i] = 0; 
                            }
                        }
                    }
                }
            }
        }
    }
    }
