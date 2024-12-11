import java.util.*;

class Strings {
    public static void main (String[] args) {
        Scanner teclado = new Scanner(System.in);
        String valor;
        String frase1 = "Primeira frase.";
        String frase2 = "Segunda frase.";
        String frase3 = "Terceira frase.";
        limpaTela();
        tela(frase1);
        valor = teclado.nextLine();
        limpaTela();
        tela(frase2);
        valor = teclado.nextLine();
        limpaTela();
        tela(frase3);
        limpaTela();
        tela(valor);
        teclado.close();
    }

    public static void tela(String S) {
        System.out.println(S);
    }

    public static void limpaTela() {
        for (int i = 1; i <= 15; ++i)
            System.out.println();
    }
}