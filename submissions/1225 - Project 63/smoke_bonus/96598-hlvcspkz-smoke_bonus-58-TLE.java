
import java.util.Scanner;

class smoke{
  public static void main (String[] args){
    Scanner scanner = new Scanner(System.in);
    int input = scanner.nextInt();
    String garbage = scanner.nextLine();
    
    for(int i = 0; i < input; i++) {
    	int N = scanner.nextInt();
   	 	int R = scanner.nextInt();
    	String dirtystinkytrash = scanner.nextLine();
      
      int[] nums = new int[N];
      
      for(int j = 0; j < N; j++) 
        nums[j] = scanner.nextInt();
      
      boolean works = true;
      int smoke1 = 0, smoke2=0;
      
      for(int k = 0; k < N; k++){  
        if(nums[k] >= smoke1)
          smoke1 = nums[k] + R;
        else if(nums[k] >= smoke2){
          if(smoke1 > smoke2) smoke2 = smoke1 + R;
        	else smoke2 = smoke2 + R;
        }
        else {
          works = false;
          break;
        }
      }
      
      if(!works) System.out.println("NO");
      else System.out.println("YES");
    }
  }
}
















