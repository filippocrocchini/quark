package it.filippocrocchini.engine.common.graphics.particles;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Updatable;

public abstract class ParticleSystem extends Updatable{
	public boolean isDirty = false;
	
	public ParticleSystem(GameObject parent) {
		super(parent);
	}
	
	public boolean isDirty() {return isDirty;}
	public abstract float[] getParticlesPositions();
	public abstract Color getColor();
}
