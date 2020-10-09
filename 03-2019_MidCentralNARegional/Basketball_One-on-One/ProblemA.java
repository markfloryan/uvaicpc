import java.util.*;

public class ProblemA{
   public static void main(String[] args){
      Scanner input = new Scanner(System.in);
      
      String line = input.nextLine();
      
      int A = 0, B = 0;
      
      for(int i = 0; i < line.length(); i+=2){
         int points = Character.getNumericValue(line.charAt(i+1));
         if(line.charAt(i) == 'A')
            A += points;
         else
            B += points;
      }
      
      if(A > B)
         System.out.println("A");
      else
         System.out.println("B");
   }
}