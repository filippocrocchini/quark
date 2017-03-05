package it.filippocrocchini.spaceship.objects;

import org.joml.Vector3f;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.graphics.Camera;
import it.filippocrocchini.engine.common.physics.RigidBody;
import it.filippocrocchini.spaceship.components.ShipGraphics;
import it.filippocrocchini.spaceship.components.controllers.PlayerController;

public class Ship extends GameObject{
	private ShipGraphics shipGraphics;
	private PlayerController playerController;
	private RigidBody rigidBody;
	private Camera shipCamera;
	
	public Ship(GameObject parent) {
		super(parent);
		transform.scale = new Vector3f(1.396f, 1, 2.972f).mul(0.7f);
		shipGraphics = new ShipGraphics(this);
		playerController = new PlayerController(this);
		rigidBody = new RigidBody(this,100,new Vector3f(0,0,0),new Vector3f(0,0,0));
		shipCamera = new Camera(this, 70f, Engine.getWindowAspectRatio(), 0.01f, 100000f);
		
		addComponent(shipGraphics);
		addComponent(rigidBody);
		addComponent(playerController);
		addComponent(shipCamera);
	}

	@Override
	public void onLoad() {		
	}

	@Override
	public void cleanup() {		
	}

	public Camera getCamera() {
		return shipCamera;
	}
}
