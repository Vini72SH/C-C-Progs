class SuperClass {
    String name;

    public void display() {
        System.out.println(this.name);
    }
}

class SubClass extends SuperClass {
    int age;

    @Override
    public void display() {
        System.out.println(this.name + " " + this.age);
    }
}

public class Her{
    public static void main(String[] args) {
        SubClass obj = new SubClass();
        SuperClass obj2 = new SuperClass();
        obj.name = "Alice";
        obj.age = 25;
        obj2.name = "Pedro";
        obj2.display();
        obj.display();
    }
}