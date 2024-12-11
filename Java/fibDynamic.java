import java.util.ArrayList;
import java.util.Collections;

public class fibDynamic {

    public static int fib(int n) {
        if (n <= 1) {
            return 1;
        }

        return fib(n - 1) + fib(n - 2);
    }

    public static int fib2 (int n, ArrayList<Integer> fibs) {
        if (n == 0 || n == 1) {
            return 1;
        }

        if (fibs.get(n) == null) {
            fibs.set(n, fib2(n - 1, fibs) + fib2(n - 2, fibs));
        }

        return fibs.get(n);
    }

    public static int dynamicFib(int n) {
        ArrayList<Integer> fibs = new ArrayList<>(Collections.nCopies(n + 1, null));
        fibs.set(0, 1);
        fibs.set(0, 1);
        return fib2(n, fibs);
    }
    public static void main(String[] args) {
        int fib1, fib2;
        System.out.println("Programação Dinâmica: Fibonacci");
        
        System.out.println("Fib recursivo: ");
        fib1 = fib(45);
        System.out.println(fib1);
        System.out.println("Fib dinâmico: ");
        fib2 = dynamicFib(45);
        System.out.println(fib2);
    }
}
