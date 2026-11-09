import java.io.*;
import java.util.StringTokenizer;

public class Verity {
        public static void main(String[] args) throws IOException {
                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

                int n = Integer.parseInt(br.readLine());

                for (int i = 0; i < n; i++){
                        StringTokenizer st = new StringTokenizer(br.readLine());
                        int N = Integer.parseInt(st.nextToken());
                        int K = Integer.parseInt(st.nextToken());
                        StringTokenizer st2 = new StringTokenizer(br.readLine());
                        String[] letters = new String[K];

                        for (int j = 0; j < K; j++){
                                letters[j] = st2.nextToken();
                        }
                        String[] guesses = new String[N];

                        for (int j = 0; j < N; j++){
                                guesses[j] = letters[0];
                        }

                        boolean[] correct = new boolean[N];
                        String answer = "";
                        for (int j = 0; j < N; j++){
                                for (int k = 0; k < K; k++){
                                        guesses[j] = letters[k];
                                        String guess = "";
                                        for (int l = 0; l < N; l++){
                                                guess += guesses[l];
                                        }
                                        bw.write(guess);
                                        bw.newLine();
                                        bw.flush();
                                        answer = br.readLine();

                                        if (answer.equals("CORRECT")){
                                                break;
                                        }
                                        for (int l = 0; l < N; l++){
                                                if(!(String.valueOf(answer.charAt(l)).equals("_"))){
                                                        guesses[l] = String.valueOf(answer.charAt(l));
                                                        correct[l] = true;
                                                }
                                        }
                                        if (correct[j] == true){
                                                break;
                                        }
                                }

                        }


                }

        br.close();
        bw.close();

        }
}
