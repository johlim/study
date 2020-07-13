package home.jhlim.java_tutorials.collection;

import java.util.ArrayList;
import java.util.Vector;
import java.util.LinkedList;

import java.util.HashSet;
import java.util.TreeSet;
import java.util.LinkedHashSet;

import java.util.Iterator;

public class ListSetDemo {

	public static void main(String[] args) {
		LinkedHashSet<String> hs = new LinkedHashSet<String>();
        hs.add("one");
        hs.add("two");
        hs.add("two");
        hs.add("three");
        hs.add("three");
        hs.add("five");
        Iterator hi = hs.iterator();
        System.out.println("\nhashset");
        while(hi.hasNext()){
            System.out.println(hi.next());
        }

        TreeSet<String> al = new TreeSet<String>();
        al.add("one");
        al.add("two");
        al.add("two");
        al.add("three");
        al.add("three");
        al.add("five");
        System.out.println("TreeSet");
        Iterator ai = al.iterator();
        while(ai.hasNext()){
            System.out.println(ai.next());
        }
        
        LinkedHashSet<String> ll = new LinkedHashSet<String>();
        ll.add("one");
        ll.add("two");
        ll.add("two");
        ll.add("three");
        ll.add("three");
        ll.add("five");
        System.out.println("LinkedHashSet");
        Iterator li = ll.iterator();
        while(li.hasNext()){
            System.out.println(li.next());
        }
        
	}

}
