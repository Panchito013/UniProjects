package simpleParkingLot;

public class parkingLot {
	
	final int MAXLOTS = 20;
	int freeLots;
	
	public parkingLot(){
		this.freeLots = MAXLOTS;
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
