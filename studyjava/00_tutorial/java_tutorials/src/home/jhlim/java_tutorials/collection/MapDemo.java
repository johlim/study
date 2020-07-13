package home.jhlim.java_tutorials.collection;

import java.util.*;

class A {
	int value;
	public int getValue()
	{
		//System.out.println("call getValue");
		return this.value;
	}
	public A(int value)
	{
		this.value = value;
	}
}
public class MapDemo {

    public static void main(String[] args) {
//        HashMap<String, Integer> a = new HashMap<String, Integer>();
//        a.put("one", 1);
//        a.put("two", 2);
//        a.put("three", 3);
//        a.put("four", 4);
        //System.out.println(a.get("one"));
        //System.out.println(a.get("two"));
        //System.out.println(a.get("three"));
         
        //iteratorUsingForEach(a);
        //iteratorUsingIterator(a);
        
        HashMap<String, A> a = new HashMap<String, A>();
        A z = new A(10);
        a.put("one", z);
        a.put("two", z);
        a.put("three", z);
        iteratorUsingForEach(a);
        
    }
     
    static void iteratorUsingForEach(HashMap map){
        Collection<Map.Entry<String, A>> entries = map.entrySet();        
        for (Map.Entry<String, A> entry : entries) {
        	A it =  entry.getValue();
            System.out.println(entry.getKey() + " : " + it.getValue());
            System.out.println(entry.getKey() + " : " + entry.getValue().getValue());
        }
    }
     
    static void iteratorUsingIterator(HashMap map){
        Set<Map.Entry<String, Integer>> entries = map.entrySet();
        Iterator<Map.Entry<String, Integer>> i = entries.iterator();
        while(i.hasNext()){
            Map.Entry<String, Integer> entry = i.next();
            System.out.println(entry.getKey()+" : "+entry.getValue());
        }
    }
}
