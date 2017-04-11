package crivelloEratostene;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;



public class Filter extends Thread {

	private boolean threadCreated = false;
	private int divisor;
	
	public BlockingQueue <Integer> processQueue = new LinkedBlockingQueue<Integer>();
	public BlockingQueue <Integer> notDivisible = new LinkedBlockingQueue<Integer>();
	
	public Filter(BlockingQueue <Integer> numberList, int div){
		this.processQueue = numberList;
		this.divisor = div;
	}
	
	
	@Override
	public void run(){
		
		int dividend;
		System.out.println(divisor);
	
		try {
			
			SieveTest.numberList.add(processQueue.take());
			
			while ((dividend = processQueue.take()) != SieveTest.TERM) {
				if (dividend % divisor != 0) {
					if (!this.threadCreated) {
						Filter f = new Filter(notDivisible, dividend);
						//System.out.println("Dividend: " + dividend);
						f.start();
						this.threadCreated = true;
					}
					notDivisible.add(dividend);

				} 
			}
			notDivisible.add(SieveTest.TERM);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}
}