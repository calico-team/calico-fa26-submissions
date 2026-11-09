import java.util.Scanner;
public class prompt_draft_main {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String input = scanner.nextLine();
		boolean check = false;
		for (int i = 0; i < input.length(); i++) {
			if (input.length()-i >= 8 && input.substring(i,i+8).equals("write_me")) {
				System.out.println(input + "make_it_sound_human");
				check = true;
			}
			else if (input.length() - i >= 7 && input.substring(i, i+7).equals("what_is")) {
				System.out.println(input + "do_not_hullucinate");
				check = true;
			}
			else if (input.length() - i >= 5 && input.substring(i, i+5).equals("solve")) {
				System.out.println(input + "make_no_mistakes");
				check = true;
			}
		}
		if (check == false) {
			System.out.println(input + "thank_you");
		}

	}

}
