package home.jhlim.java_tutorials.generic;

class Persion <T>{
	public T info;
}
public class GenericDemo {

	public static void main(String[] args) {
		Persion<String> p1 = new Persion<String>();
		Persion<StringBuilder> p2 = new Persion<StringBuilder>();
		
		System.out.println(p1.info);
		System.out.println(p2.info);
	}

}
