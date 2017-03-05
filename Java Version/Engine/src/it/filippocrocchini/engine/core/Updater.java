package it.filippocrocchini.engine.core;

import java.util.ArrayList;
import java.util.List;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.component.Updatable;

public class Updater extends Thread{
	
	private List<Updatable> updatables;
	
	private volatile double deltaTime;
	
	public Updater(String threadName) {
		super(threadName);
		
		updatables = new ArrayList<Updatable>();
	}

	@Override
	public void run() {	
		long currentTime, lastTime = System.nanoTime();
		
		while(Engine.isRunning()) {
			currentTime = System.nanoTime();
			deltaTime = (currentTime - lastTime)/1000000.0;
			lastTime = currentTime;
						
			for (int i = 0 ; i < updatables.size(); i++) {
				if(updatables.get(i).isEnabled())
					updatables.get(i).update(getDeltaTime());
			}
						
			try {
				Thread.sleep(1);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		//TODO: Look at the Engine class -> DESTROY_ENGINE Thread
		Engine.stop();
	}
	
	public void registerUpdatable(Updatable u) {
		updatables.add(u);
	}
	
	public void unRegisterUpdatable(Updatable u) {
		while(updatables.remove(u));
	}

	public double getDeltaTime() {
		return deltaTime;
	}

}
