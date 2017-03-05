package it.filippocrocchini.engine.core.resource;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.resource.FutureResource;

public class ResourceLoader extends Thread{
	public volatile BlockingQueue<FutureResource<?>> toLoad;
				
	public ResourceLoader(String threadName, int maxQueue) {
		super(threadName);
		toLoad = new ArrayBlockingQueue<FutureResource<?>>(maxQueue);
	}
	
	@Override
	public void run() {
		while(Engine.isRunning()) {
				if(toLoad.isEmpty()) {
					synchronized (toLoad) {
						try {
							toLoad.notify();
							toLoad.wait();
						} catch (InterruptedException e) {
							return;
						} 
					}
				}
				
				while(!toLoad.isEmpty() && Engine.isRunning()) {
					FutureResource<?> r;
					
					synchronized (toLoad) {
						r = toLoad.poll();
						toLoad.notify();
					}
					
					try {
						r.rawLoad();
					} catch(AssertionError | Exception  e) {
						e.printStackTrace();
					}
					Engine.renderer.registerResource(r);
				}			
		}
		
		synchronized (toLoad) {
			toLoad.notifyAll();
		}
	}
	
	

	public void loadResource(FutureResource<?> r) {
		if(!Engine.isRunning()) return;
		
		try {
			synchronized (toLoad) {
				try{
					toLoad.add(r);
				} catch (IllegalStateException e1){
					e1.printStackTrace();
					toLoad.wait();
					toLoad.add(r);
					System.out.println("Full queue...");
				}
				toLoad.notify();
			}
		} catch (InterruptedException e) {
			return;
		}
	}
}
