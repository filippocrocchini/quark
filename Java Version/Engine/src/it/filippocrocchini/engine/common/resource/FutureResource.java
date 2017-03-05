package it.filippocrocchini.engine.common.resource;

import java.io.IOException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class FutureResource<T extends Resource> implements Future<T>{
	private volatile Object loadedLock = new Object();
	private boolean isCancelled = false;
	private boolean completedRawLoad = false;
	private boolean completedGlLoad = false;
	
	private T resource;
	
	public FutureResource(T resource) {
		this.resource = resource;
	}

	public void rawLoad(){
		try {
			resource.onRawLoad();
		} catch (IOException e1) {
			e1.printStackTrace();
			cancel(true);
			return;
		}
		
		completedRawLoad = true;				
		System.out.println("Raw Loaded " + resource.getClass().getSimpleName());
	}
	
	public void glLoad() {
		if(isCancelled()) return;
		
		try {
			resource.onGlLoad();
		} catch (AssertionError e) {
			e.printStackTrace();
			cancel(true);
			return;
		}
		
		completedGlLoad = true;
		System.out.println("GL Loaded " + resource.getClass().getSimpleName());
		
		synchronized (loadedLock) {
			loadedLock.notifyAll();
		}
	}
	
	public boolean isRawLoaded() {
		return completedRawLoad;
	}
	
	public boolean isGlLoaded() {
		return completedGlLoad;
	}
	

	@Override
	public boolean cancel(boolean mayInterruptIfRunning) {
		isCancelled = mayInterruptIfRunning;
		System.err.println("Cancelled resource.");

		synchronized (loadedLock) {
			loadedLock.notifyAll();
		}
		
		return isCancelled;
	}

	@Override
	public T get() throws InterruptedException, ExecutionException {
		if(isCancelled()) return null;
		if(isDone()) return resource;
		
		synchronized (loadedLock) {
			loadedLock.wait();
		}
		
		if(isCancelled()) return null;
		return resource;
	}

	@Override
	public T get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
		if(isCancelled()) return null;
		if(isDone()) return resource;
		
		synchronized (loadedLock) {
			loadedLock.wait(unit.toMillis(timeout));
		}
			
		if(isDone())return resource;
		return null;
	}

	@Override
	public boolean isCancelled() {
		return isCancelled;
	}

	@Override
	public boolean isDone() {
		return isRawLoaded() && isGlLoaded();
	}

	public void cleanup() {
		if(!isCancelled())
			resource.glCleanup();
	}
	
	
}
