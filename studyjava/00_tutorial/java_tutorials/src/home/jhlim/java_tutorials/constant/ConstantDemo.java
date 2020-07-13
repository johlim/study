package home.jhlim.java_tutorials.constant;

enum Fruit {
	APPLE("red"), PEACH("pink"), BANANA("yellow");
	public String color;
	public String getColor() {
		return this.color;
	}
	
	Fruit(String color)
	{
		System.out.println("Call Constant "+this);
		this.color = color;
	}
}
public class ConstantDemo {

	public static void main(String[] args) {
		for ( Fruit f  :  Fruit.values()) {
			System.out.println(f);
			System.out.println(f.color);
			System.out.println(f.getColor());
		}

	}

}
