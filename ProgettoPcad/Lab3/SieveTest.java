package crivelloEratostene;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class SieveTest {
	final static int TERM = -1;
	final public static int N = 50;
	static BlockingQueue<Integer> numberList = new LinkedBlockingQueue<Integer>();
	
	
	
	
	public static void main(String[] args){
		
		for(int i = 2; i <= N ; i++){
			numberList.add(i);
		}
		
		numberList.add(TERM); // Numero di terminazione 
		
		Filter f1 = new Filter(numberList, numberList.element());

		
	
		f1.start();
		
		try {
			f1.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
	}

}
