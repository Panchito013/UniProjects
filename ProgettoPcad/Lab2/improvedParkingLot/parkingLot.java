package improvedParkingLot;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class parkingLot {
	
	private final int MAXLOTS = 20;
	private int freeLots;
	final Lock barrier = new ReentrantLock();
	final Condition queueA = barrier.newCondition();
	final Condition queueB = barrier.newCondition();
	
	
	public parkingLot(){
		this.freeLots = MAXLOTS;
	}
	
	public int getFreeLots(){
		return freeLots;
	}
	
	public void entranceA(){
		barrier.lock();
		while(this.freeLots == 0){
			System.out.println("parkingLot is FULL");
			try {
				queueA.await();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		this.freeLots--;
		barrier.unlock();
	}
	
	public void entranceB(){
		barrier.lock();
		while(this.freeLots == 0){
			System.out.println("parkingLot is FULL");
			try {
				queueB.await();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		this.freeLots--;

		barrier.unlock();
	}
	
	public void exit(){
		barrier.lock();
		this.freeLots++;
		queueA.signalAll();
		queueB.signalAll();
		barrier.unlock();
	}
}
