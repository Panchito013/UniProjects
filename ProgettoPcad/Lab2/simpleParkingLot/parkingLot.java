package simpleParkingLot;

public class parkingLot {
		
	private final int MAXLOTS = 20;
	public volatile int freeLots;
	
	public parkingLot(){
		this.freeLots = MAXLOTS;
	}
		
	synchronized void entrance(){
		while(freeLots == 0){
			System.out.println("parkingLot is FULL");
			try {
				this.wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		freeLots--;
		

	}
	
	synchronized void exit(){
		freeLots++;
		notifyAll();
	}

}
