package simpleParkingLot;

public class parkingLot {
	
	private final int MAXLOTS = 20;
	private int freeLots;
	
	public parkingLot(){
		this.freeLots = MAXLOTS;
	}
	
	public int getFreeLots(){
		return freeLots;
	}
	
	synchronized void entrance(){
		while(this.freeLots == 0){
			System.out.println("parkingLot is FULL");
			try {
				this.wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		this.freeLots--;
	}
	
	
	synchronized void exit(){
		this.freeLots++;
		notifyAll();
	}

}
