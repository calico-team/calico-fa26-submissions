import java.util.Scanner;

public class p3 {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int trials = scanner.nextInt();
        for(int i = 0; i < trials; i++) {
          int n = scanner.nextInt();
          int k = scanner.nextInt();
          
          char[] letters = new char[k];
          for(int j = 0; j < k; j++) {
            letters[j] = scanner.next().charAt(0);
          }

          char[] guess = new char[n];
          boolean[] known = new boolean[n];
          int[] tried = new int[n];

          while(true) {
            for(int a = 0; a < n; a++) {
              if (!known[a]) {
                guess[a] = letters[tried[a]];
              }
            }

            System.out.println(new String(guess));
            System.out.flush(); // i hope this is the right thing to do i lowkey don't know kljflk;djsafkl;dsajflkdsa; why did i no t review java beforehand 

            String response = scanner.next();
              if (response.equals("CORRECT")) {
                break;
              }

            for (int m = 0; m < n; m++){
              if(response.charAt(m) != '_') {
                known[m] = true;
              } else {
                tried[m]++;
              }
            }
          }
      }
  }
}
