package it.filippocrocchini.engine.common.physics;

import org.joml.Vector3f;

import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Updatable;

public class RigidBody extends Updatable{
	
	//TODO: Make private
	public Vector3f velocity = new Vector3f();
	
	//NOTE: Unused
	public Vector3f angularVelocity = new Vector3f();

	public double mass = 1;

	private Vector3f frameDeltaSpeed;
	private Vector3f frameDeltaAngularVelocity;
	private Vector3f impulseDelta;
	
	public RigidBody(GameObject parent, float mass, Vector3f initialVelocity, Vector3f initialAngVelocity) {
		super(parent);
		this.mass = mass;
		velocity.set(initialVelocity);
		angularVelocity.set(initialAngVelocity);
		frameDeltaSpeed = new Vector3f();
		frameDeltaAngularVelocity = new Vector3f();;
		impulseDelta = new Vector3f();;
	}

	@Override
	public void update(double delta) {
		frameDeltaSpeed.set(velocity).mul((float)delta);
		frameDeltaAngularVelocity.set(angularVelocity).mul((float)delta);
		
		//FIXME: TEMP
		//parentGameObject.transform.localRotation.transform(frameDeltaSpeed);
		
		parentGameObject.transform.rotateLocal(frameDeltaAngularVelocity);
		parentGameObject.transform.position.add(frameDeltaSpeed);
	}
	
	public void applyImpulse(Vector3f force, Vector3f point, double delta) {
		impulseDelta.set(force).mul((float) (1/mass * delta));
		velocity.add(impulseDelta);
		//angularMomentum.add(v)
	}
	
	

}
