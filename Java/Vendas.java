import java.util.*;
public class Vendas {
    public static void main(String[] args) {
        int qtde;
        double produto = 100.0;
        double comissao;
        Scanner teclado = new Scanner(System.in);
        for (int i = 1; i < 30; ++i) {
            System.out.println("Digite a quantidade de vendas");
            qtde = teclado.nextInt();
            if (qtde <= 10) {
                comissao = comissao(10, qtde, produto);
            } else if (qtde < 30) {
                comissao = comissao(12, qtde, produto);
            } else {
                comissao = comissao(15, qtde, produto);
            }
            System.out.println("O valor da comissão é: " + comissao);
        }
        teclado.close();
    }

    public static double comissao(double perc, int quantidade, double valorProduto) {
        double valorComissao = (perc * quantidade * valorProduto) / 100;
        return valorComissao;
    }
}
