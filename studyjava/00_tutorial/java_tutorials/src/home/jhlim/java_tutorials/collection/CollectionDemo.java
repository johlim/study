package home.jhlim.java_tutorials.collection;

import java.util.*;

class Computer implements Comparable {
	int serial;
	String owner;
	Computer(int serial, String owner)
	{
		this.serial = serial;
		this.owner = owner;
	}
	public int compareTo(Object o) 
	{
		return this.serial - ((Computer)o).serial;
	}
	
    public String toString(){
        return serial+" "+owner;
    }
}

public class CollectionDemo {

	public static void main(String[] args) {
        List<Computer> computers = new ArrayList<Computer>();
        computers.add(new Computer(500, "egoing"));
        computers.add(new Computer(200, "leezche"));
        computers.add(new Computer(3233, "graphittie"));

        System.out.println("before");
        Iterator i = computers.iterator();
        while(i.hasNext()){
            System.out.println(i.next());
        }
        Collections.sort(computers); // static method므로 호출가능
        System.out.println("\nafter");
        i = computers.iterator();
        while(i.hasNext()){
            System.out.println(i.next());
        }
	}

}
