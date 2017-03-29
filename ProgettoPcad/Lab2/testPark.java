package simpleParkingLot;

public class testPark{
		
	public static void main(String[] args){
		
		if(args.length != 1){
			System.out.println("Usage: ./parkingLot [N-cars] [K-attempts]\n");
			return;
		}
		
		int N = Integer.parseInt(args[0]);
		//int K = Integer.parseInt(args[1]);
		
		parkingLot park = new parkingLot();
		carThread[] cars = new carThread[N];
		
		for(int i = 0; i < N; i++)
			cars[i] = new carThread("Car n°" + (i+1), park);
		
		System.out.println("===== parkingLot is OPEN =====");
		
		
		for(int i = 0; i < N; i++)
			cars[i].start();
		try {
			for(int i = 0; i < N; i++)
				cars[i].join();
			
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("===== parkingLot is CLOSED =====");
		
	}
}
	

