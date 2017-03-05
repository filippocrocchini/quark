package it.filippocrocchini.spaceship.objects;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.spaceship.components.TestParticleSystem;

public class Debris extends GameObject{
	private TestParticleSystem pSystem;
	
	public Debris(GameObject parent, Color c) {
		super(parent);
		pSystem = new TestParticleSystem(this, c);
		addComponent(pSystem);
	}

	@Override
	public void onLoad() {		
	}

	@Override
	public void cleanup() {		
	}

}
