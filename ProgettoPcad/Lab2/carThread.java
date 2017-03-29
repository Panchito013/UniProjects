package simpleParkingLot;

public class carThread extends Thread {
	
	parkingLot park;
	private int attempt = 0;
	private int iteration = 0;
	
	
	
	public carThread(String name, parkingLot park, int iterations){
		super(name);
		this.park = park;
		this.iteration = iterations;
	}
	
	public synchronized void run(){
		while (this.attempt < this.iteration){
			try {
				sleep(3000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			park.entrance();
			//System.out.println("Attempt car: " + this.getName() + "\t\tattempt: " + (attempt+1));
			System.out.println("Enters car: " + this.getName() + "\t\tfree lots: " + park.freeLots);
			try {
				sleep(3000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			park.exit();
			System.out.println("Exits car: " + this.getName() + "\t\tfree lots: " + park.freeLots);
			
			this.attempt++;
		}

	}

}
