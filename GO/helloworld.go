package main

import "fmt"

type MyInt int
var i int
var j MyInt

func doSomething(c chan int) {
		for i:=0; i < 10; i++ {
		fmt.Println("Hello, 세계");
		}
	c<-1
}

func main(){
	j = MyInt(i)
	c := make(chan int)

	go doSomething(c)

	<-c
	fmt.Println("Ending");

}

