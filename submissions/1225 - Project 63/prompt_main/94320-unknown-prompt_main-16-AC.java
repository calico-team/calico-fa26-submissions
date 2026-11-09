import java.util.Scanner;

class prompt {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int input = scanner.nextInt();
    String garbage = scanner.nextLine();
    
    String[] sentences = new String[input];
    for (int i=0;i<input;i++){
      sentences[i] = scanner.nextLine();
    }
    
    for(int i = 0; i < input; i++) {
      if(sentences[i].indexOf("write_me") >= 0)
        System.out.println(sentences[i]+"make_it_sound_human");
      else if(sentences[i].indexOf("what_is") >= 0)
        System.out.println(sentences[i]+"do_not_hallucinate");
      else if (sentences[i].indexOf("solve")>=0)
        System.out.println(sentences[i]+"make_no_mistakes");
			else
        System.out.println(sentences[i] + "thank_you");
    }
  }
}