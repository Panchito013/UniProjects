package protocol;

import java.util.concurrent.ExecutionException;

public class MainClass  {
	
	final static int nThreads = 5;
	
	public static void main(String[] args){
		
		ConnectionPool pool = new ConnectionPool(nThreads);
		
		if(args.length != 1){
			System.out.println("Usage: ./connectionPool [URL]\n");
			return;
		}
		
		String url = args[0];
	
			new Thread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					try {
						System.out.println(pool.request(url));
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (ExecutionException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				
			}).start();
	
		
		new Thread(new Runnable(){

			@Override
			public synchronized void run() {
				// TODO Auto-generated method stub
				
				try {
					
					wait(5000);
					System.out.println(pool.request("http://www.google.com"));
					wait(10000);
					System.out.println(pool.request("http://www.bing.com"));
				
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (ExecutionException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
		}).start();
		
		
				
	}

}
