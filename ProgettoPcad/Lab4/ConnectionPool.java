package protocol;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;


public class ConnectionPool {
		
	private final int CLIENTERROR = 4;
	private final int REDIRECTERROR = 3;
	private final int SERVERERROR = 5;
	private final int OKSTATUS = 2;
	
	ExecutorService threadExecutor;

	
	
	public ConnectionPool(int size){
		threadExecutor = Executors.newFixedThreadPool(size);
		System.out.println("PoolThread Created");
	}
	
	
	private Callable<String> TaskCreator(String urlink){
		
		Callable<String> task = new Callable<String>(){

			@Override
			public String call() throws Exception {
				// TODO Auto-generated method stub
				URL url;
				String page = "";
				int responseCode = 404;
				
				url = new URL(urlink);
				HttpURLConnection connection = (HttpURLConnection) url.openConnection();
				responseCode = connection.getResponseCode();
				
				BufferedReader read = new BufferedReader(new InputStreamReader(connection.getInputStream()));
				String content = read.readLine();
				
				while(content!=null){
					page += content;
					content = read.readLine();
					page += '\n';
				}
				return String.valueOf(responseCode) + page;	
			}
			
		};
		return task;
	}
	
	public String request(String url) throws InterruptedException, ExecutionException{
		if(!threadExecutor.isTerminated()){
			Future<String> response = threadExecutor.submit(TaskCreator(url));
			
			if(response.get().substring(0, 1).equals(String.valueOf(OKSTATUS)))
				return "\nPage Response\n\n" + response.get().substring(3);
			
			if (response.get().substring(0, 1).equals(String.valueOf(REDIRECTERROR)))
				return "\n\nPage Response\n\nError: "+response.get() + " Need Redirection";
			
			
			if (response.get().substring(0, 1).equals(String.valueOf(CLIENTERROR)))
				return "\n\nPage Response\n\nError: "+response.get() + " Client Error";
			
			
			if (response.get().substring(0, 1).equals(String.valueOf(SERVERERROR)))
				return "\n\nPage Response\n\nError: "+response.get() + " Server Error";
			
			return "Error "+ response.get();
				
		}
		return url;
		
	}
	
	

	
	
	public void stop(){
		threadExecutor.shutdown();
	}
	
}
