import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String answer = "";
        String newGame= "yes";

        while (newGame.equalsIgnoreCase("Yes")){
            System.out.println("TIC - TAC - TOE");
            System.out.println("\nWelcome to the game!!!");
            System.out.println("Which player wants to start first?\nX or O ");

            answer= scanner.nextLine();
            while(!answer.equalsIgnoreCase("x") && !answer.equalsIgnoreCase("o")){

                System.out.println("Please, ender again the player. X or O");
                answer= scanner.nextLine();

                System.out.println(answer);

            }
            Design design = new Design(answer);
            System.out.println("\n#####################################\n");
            System.out.println("Do you want to continue to a new game?\n(If yes, write 'Yes' )");
            newGame = scanner.nextLine();

        }


    }
}

