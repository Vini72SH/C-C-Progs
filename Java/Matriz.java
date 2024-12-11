public class Matriz {
    public static void main (String[] args) {
        int a[][] = {{2,3,1}, {4,5,1}, {2, 4, 8}};
        int mult[][] = new int[3][3];

        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {
                mult[i][j] = 3 * a[i][j];
            }
        }
        System.out.println("Matriz 1: ");
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {
                System.out.print(" " + a[i][j]);
            }
            System.out.println(" ");
        }
        System.out.println("Matriz 2: ");
        for (int i = 0; i < mult.length; i++) {
            for (int j = 0; j < mult[i].length; j++) {
                System.out.print(" " + mult[i][j]);
            }
            System.out.println(" ");
        }
    }
}
