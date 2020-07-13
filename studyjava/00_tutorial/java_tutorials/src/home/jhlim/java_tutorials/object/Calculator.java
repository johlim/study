package home.jhlim.java_tutorials.object;

final class Calcu{
    int left, right;
      
    public void setOprands(int left, int right){
        this.left = left;
        this.right = right;
    }
      
    public void sum(){
        System.out.println(this.left+this.right);
    }
      
    public void avg(){
        System.out.println((this.left+this.right)/2);
    }
    
    protected void breif(){
    	int []localsum = {left,right};
    	
    	for(int i=0; i<2; i++)
    	{   
    		System.out.print("title \n");
    		System.out.println(localsum[i]);	
    	}
        
    }    
}
  
class Calculator {
      
    public static void main(String[] args) {
          
        Calcu c1 = new Calcu();
        c1.setOprands(10, 20);
        c1.sum();       
        c1.avg();       
          
        Calcu c2 = new Calcu();
        c2.setOprands(20, 40);
        c2.sum();       
        c2.avg();
        c2.breif();
    }
  
}