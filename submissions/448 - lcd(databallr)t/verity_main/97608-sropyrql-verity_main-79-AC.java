import java.util.Scanner;

public class thing {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int testCA = input.nextInt();
        
        for(int i = 0; i < testCA; i++) {
            int length = input.nextInt();
            int numTypes = input.nextInt();
            
            String[] letters = new String[numTypes];
            for (int j = 0; j < numTypes; j++) {
                letters[j] = input.next();
            }
            String[] answer = new String[length];
            for (int j = 0; j < length; j++) {
                answer[j] = "_";
            }
            
            boolean solvedEarly = false;
            
            for(int j = 0; j < letters.length - 1; j++) {
                String thing = "";
                for(int k = 0; k < length; k++) {
                    thing += letters[j];
                }
                System.out.println(thing);
                System.out.flush();
                
                String response = input.next();
                if(response.equals("CORRECT")) {
                    solvedEarly = true;
                    break;
                }
                
                for(int k = 0; k < response.length(); k++) {
                    String character = response.substring(k, k + 1);
                    if(character.equals("_")) {
                        continue;
                    }
                    answer[k] = character;
                }
            }
            if (!solvedEarly) {
                String lastLetter = letters[numTypes - 1];
                for (int j = 0; j < length; j++) {
                    if (answer[j].equals("_")) {
                        answer[j] = lastLetter;
                    }
                }
                String finalTing = "";
                for(int j = 0; j < answer.length; j++) {
                    finalTing += answer[j];
                }
                System.out.println(finalTing);
                System.out.flush();
                String status = input.next();
            }
        }
        input.close();
    }
}