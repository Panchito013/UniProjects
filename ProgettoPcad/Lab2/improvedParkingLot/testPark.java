package improvedParkingLot;

import improvedParkingLot.carThread;


public class testPark {
	
	
public static void main(String[] args){
		
		if(args.length != 2){
			System.out.println("Usage: ./parkingLot [N-cars] [K-attempts]\n");
			return;
		}
		
		int N = Integer.parseInt(args[0]);
		int K = Integer.parseInt(args[1]);
		int[] R = new int[N];

		
		parkingLot park = new parkingLot();
		carThread[] cars = new carThread[N];
		
		for(int i = 0; i < N; i++)
			R[i] =  (int) (Math.random()*2) + 1;

		for(int i = 0; i < N; i++){
			cars[i] = new carThread("Car n°" + (i+1), park, K, R[i]);
			System.out.println(R[i]);
		}
		
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
