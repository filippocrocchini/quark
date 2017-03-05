package it.filippocrocchini.spaceship.objects.asteroid;

import org.joml.Vector3f;

import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.physics.RigidBody;
import it.filippocrocchini.engine.core.Utils;
import it.filippocrocchini.spaceship.components.AsteroidGraphics;

public class Asteroid extends GameObject{
	private AsteroidGraphics graphics;
	private RigidBody rigidBody;
	
	public Asteroid(GameObject parent) {
		super(parent);
		graphics = new AsteroidGraphics(this);
		
		Vector3f ispeed = new Vector3f((float) Math.random(), (float) Math.random(), (float)Math.random());
		
		rigidBody = new RigidBody(this, 10000, ispeed.mul(0.01f), new Vector3f(0.0001f,0.0001f,0.0001f));
		addComponent(graphics);
		addComponent(rigidBody);
		
		transform.scale.mul(1f + Utils.gaussianRandom() * 2f);
		transform.rotateLocal((float) (Math.random() * Math.PI * 2), (float) (Math.random() * Math.PI * 2), (float) (Math.random() * Math.PI * 2));

	}

	@Override
	public void onLoad() {
	}

	@Override
	public void cleanup() {
	}

}
