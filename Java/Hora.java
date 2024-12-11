import java.text.*;
import java.util.*;
public class Hora {
    public static void main (String[] args) {
        SimpleDateFormat formatter = new SimpleDateFormat();
        String dateString = formatter.format(new Date());
        System.out.println("Horário: " + dateString);
    }
}
