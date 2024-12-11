import java.util.Scanner;

class Pessoa{
    private String nome;
    private String email;

    public Pessoa (String nome, String email) {
        this.nome = nome;
        this.email = email;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void mostraNome() {
        System.out.println("O nome desta pessoa é: " + this.nome);
    }

    public void mostraEmail() {
        System.out.println("O email desta pessoa é: " + this.email);
    }
}

class Aluno extends Pessoa{
    private int GRR;

    public Aluno(String nome, String email, int GRR) {
        super(nome, email);
        this.GRR = GRR;
    }

    public void setGRR(int GRR) {
        this.GRR = GRR;
    }

    public void mostraGRR() {
        System.out.println("O GRR desta pessoa é: " + this.GRR);
    }
}

public class GerenAlunos{
    public static void main(String[] args) {
        String n, e;
        int grr;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextLine();
        e = scanner.nextLine();
        grr = scanner.nextInt();

        Aluno teste = new Aluno(n, e, grr);
        teste.mostraNome();
        teste.mostraEmail();
        teste.mostraGRR();

        scanner.close();
    }
}