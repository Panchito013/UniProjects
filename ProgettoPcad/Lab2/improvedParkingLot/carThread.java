package improvedParkingLot;

import improvedParkingLot.parkingLot;

public class carThread extends Thread{
	
	parkingLot park;
	private int attempt = 0;
	private int iteration = 0;
	private int random;
	
	
	public carThread(String name, parkingLot park, int iterations, int randomicity){
		super(name);
		this.park = park;
		this.iteration = iterations;
		this.random = randomicity;
	}
	
	public void run(){
		while (this.attempt < this.iteration){
			try {
				sleep(3000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			if(random == 1){
				park.entranceA();
				System.out.println("Enters car on entrance A: " + this.getName() + "\t\tfree lots: " + park.getFreeLots());
			}
			
			if(random == 2){
				park.entranceB();
				System.out.println("Enters car on entrance B: " + this.getName() + "\t\tfree lots: " + park.getFreeLots());
			}	
			
			park.exit();
			System.out.println("Exits car: " + this.getName() + "\t\tfree lots: " + park.getFreeLots());
			
			this.attempt++;
		}
	}	
}
