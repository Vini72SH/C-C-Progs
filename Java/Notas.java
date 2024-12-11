import java.io.*;

public class Notas {
    public static void main(String[] args) throws IOException {
        int i;
        double notas [] = new double[4];
        double soma = 0.0;
        double media;
        BufferedReader teclado = new BufferedReader(new InputStreamReader((System.in)));
        for (i = 0; i < 4; i++) {
            notas[i] = Double.parseDouble(teclado.readLine());
            soma = soma + notas[i];
        }
        media = soma / 4;
        System.out.println("A média é: " + media);
        for (i = 0; i < 4; i++) {
            System.out.println("A nota " + (i + 1) + " é " + notas[i]);
        }
    }
}
