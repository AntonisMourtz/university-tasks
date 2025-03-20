public class Design {
    String[][] table= new String[3][3];
    String position="" ;
    Design(String answer){

        //I make the table
        for(int i=0; i<table.length; i++){
            for (int j=0; j<table[i].length; j++){
                table[i][j] =" ";
            }
        }

        while(!answer.equals("stop")){

            if(answer.equalsIgnoreCase("x")){

                System.out.println("PLAYER -X-");
                makeTable();

                PlayerX playerx = new PlayerX();
                //System.out.println(playerx.position);

                int pos1 = playerx.position.charAt(0)-48;// ASCII
                int pos2 = playerx.position.charAt(1)-48;
                //System.out.println(pos1+"   "+pos2);

                //I check if exist something in this position
                while(!table[pos2-1][pos1-1].isBlank()) {
                    System.out.println("PLAYER -X-");
                    makeTable();
                    System.out.println("\nWrong position. Please try again!!!");

                    PlayerX playerx2 = new PlayerX();

                     pos1 = playerx2.position.charAt(0)-48;// ASCII
                     pos2 = playerx2.position.charAt(1)-48;

                }

                table[pos2-1][pos1-1] = "X";

                answer = "O";
            }
            //tester for x
            for(int i=0; i<3; i++){

                if(table[i][0].equals("X")&&table[i][1].equals("X")&&table[i][2].equals("X")){
                    answer="stop";
                    makeTable();
                    System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

                } else if(table[0][i].equals("X")&&table[1][i].equals("X")&&table[2][i].equals("X")) {
                    answer="stop";
                    makeTable();
                    System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

                }

            }
            if(table[0][0].equals("X")&&table[1][1].equals("X")&&table[2][2].equals("X")){
                answer="stop";
                makeTable();
                System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

            } else if (table[2][0].equals("X")&&table[1][1].equals("X")&&table[0][2].equals("X")) {
                answer="stop";
                makeTable();
                System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );
            }

            if(answer.equalsIgnoreCase("o")){
                System.out.println("PLAYER -O-");
                makeTable();

                PlayerO playerO = new PlayerO();


                int pos1 = playerO.position.charAt(0)-48;
                int pos2 = playerO.position.charAt(1)-48;



                while(!table[pos2-1][pos1-1].isBlank()) {
                    System.out.println("PLAYER -O-");
                    makeTable();
                    System.out.println("\nWrong position. Please try again!!!");

                    PlayerO playerO2 = new PlayerO();


                    pos1 = playerO2.position.charAt(0)-48;
                    pos2 = playerO2.position.charAt(1)-48;


                }

                table[pos2-1][pos1-1] = "O";

                answer = "X";

            }

            //tester for O
            for(int i=0; i<3; i++){

                    if(table[i][0].equals("O")&&table[i][1].equals("O")&&table[i][2].equals("O")){
                        answer="stop";
                        makeTable();
                        System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

                    } else if(table[0][i].equals("O")&&table[1][i].equals("O")&&table[2][i].equals("O")) {
                        answer="stop";
                        makeTable();
                        System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

                    }

            }
            if(table[0][0].equals("O")&&table[1][1].equals("O")&&table[2][2].equals("O")){
                answer="stop";
                makeTable();
                System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

            } else if (table[2][0].equals("O")&&table[1][1].equals("O")&&table[0][2].equals("O")) {
                answer="stop";
                makeTable();
                System.out.println("\n\nCongratulations!!! \nPLAYER -O- You are the Winner!" );

            }

        }

    }
    void makeTable(){

           System.out.print    ("  -  A  -  B  -  C  -");
           System.out.print("\n  ###################");
           for(int i=0; i<table.length; i++){
               System.out.println();
               for (int j=0; j<table[i].length; j++){
                   System.out.print("  |  ");

                   System.out.print(table[i][j]);
               }

               System.out.print("  |  "+ (i+1));

           }
        System.out.println("\n  ###################");
   }

}
