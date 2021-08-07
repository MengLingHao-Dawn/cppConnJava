public class Sample{
    public String name;

    public static String sayHello(String name,int year){
        return "Hello," + name + year + "!";
    }

    public String sayHello(){
        return "Hello," + name + "!";
    }
}