import java.util.Scanner;
public class PlayerO {
    String position;

    PlayerO(){
        msgo();

        Scanner scanner = new Scanner(System.in);
        position = scanner.nextLine();

        //I change the position in upper case
        position = position.toUpperCase();



        while(!(position.length()==2) || ((!(position.charAt(0)=='A')&&!(position.charAt(0)=='B')&&!(position.charAt(0)=='C'))  ||  (!(position.charAt(1)=='1')&&!(position.charAt(1)=='2')&&!(position.charAt(1)=='3')))){

            System.out.println("The position is not correct. Please try again");
            position = scanner.nextLine();


            position = position.toUpperCase();

        }

        //I transform the letters to numbers
        if(position.charAt(0)=='A'){
            position = position.replace('A', '1');
        }
        if(position.charAt(0)=='B'){
            position = position.replace('B', '2');
        }
        if(position.charAt(0)=='C'){
            position = position.replace('C', '3');
        }

    }

    void msgo(){
        System.out.println();
        System.out.println("Select the O position (e.g. A1, B3, C2)");
    }

}